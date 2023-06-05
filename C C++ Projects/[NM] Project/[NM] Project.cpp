#include <iostream>
#include <pbPlots.cpp>
#include <supportLib.cpp>

const int MAX_DEGREE = 11; // Максимальная степень полинома

void plot(vector<double> x, vector<double> forecast, string plotname) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* seriesForecast = GetDefaultScatterPlotSeriesSettings();
    seriesForecast->xs = &x;
    seriesForecast->ys = &forecast;
    seriesForecast->lineType = toVector(L"solid");
    seriesForecast->pointType = toVector(L"circles");
    seriesForecast->linearInterpolation = true;
    seriesForecast->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesForecastCircles = GetDefaultScatterPlotSeriesSettings();
    seriesForecastCircles->xs = &x;
    seriesForecastCircles->ys = &forecast;
    seriesForecastCircles->lineType = toVector(L"solid");
    seriesForecastCircles->pointType = toVector(L"circles");
    seriesForecastCircles->linearInterpolation = false;
    seriesForecastCircles->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Temperature forecast");
    settings->xLabel = toVector(L"Days");
    settings->yLabel = toVector(L"Temperature");

    vector<ScatterPlotSeries*> series({ seriesForecast, seriesForecastCircles });

    for (int i = 0; i < series.size(); i++) {
        settings->scatterPlotSeries->push_back(series[i]);
    }

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, plotname);
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

struct Date {
    int day;
    int month;
    int year;
};

void fractionalPolynomial(double degree, double* x, double* y, double* coef)
{
    double n = degree + 1;
    cout << "(int)n" << (int)n << " (double)n" << n << "\n";


    double** A = new double* [(int)n];
    double* B = new double[(int)n];
    
    double i_d = 0;
    double j_d = 0;
    for (double i = 0; i < n; i += 1 + (1.0 / n)) {
        A[(int)i] = new double[(int)n];
        B[(int)i] = 0;
        for (double j = 0; j < n; j += 1 + (1.0 / n)) {
            A[(int)i][(int)j] = 0;
            for (int k = 0; k < MAX_DEGREE; k++) {
                A[(int)i][(int)j] += pow(x[k], i + j);
            }
        }
        for (int k = 0; k < MAX_DEGREE; k++) {
            B[(int)i] += y[k] * pow(x[k], i);
        }
    }

    //std::cout << "A: \n";
    for (int i = 0; i < (int)n; i++)
    {
        for (int j = i + 1; j < (int)n; j++)
        {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < (int)n; k++)
            {
                A[j][k] -= factor * A[i][k];
                //std::cout << A[j][k] << " ";
            }
            //std::cout << "\n";
            B[j] -= factor * B[i];
        }
    }

    //std::cout << "B: \n";
    for (int i = n - 1; i >= 0; i--)
    {
        coef[i] = B[i];
        //std::cout << B[i] << "\n";
        for (int j = i + 1; j < n; j++)
        {
            coef[i] -= A[i][j] * coef[j];
        }
        coef[i] /= A[i][i];
    }

    for (int i = 0; i < (int)n; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    delete[] B;
}

int getTotalDays(Date date) {
    int monthDays[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
    int totalDays = (date.year - 2020) * 365 + (date.year - 2020) / 4;
    totalDays += monthDays[date.month - 1];
    if ((date.month > 2) && (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0))) {
        totalDays++;
    }
    totalDays += date.day;
    return totalDays;
}

int main()
{
    Date testiks[MAX_DEGREE];
    for (int i = 0; i < MAX_DEGREE; i++) {
        testiks[i].day = i + 1;
        testiks[i].month = 1;
        testiks[i].year = 2020;
    }

    double x[MAX_DEGREE]; // Значения x

    for (int i = 0; i < MAX_DEGREE; i++) {
        x[i] = getTotalDays(testiks[i]);
    }

    double y[MAX_DEGREE] = { 19, 14, 13, 15, 13, 5, 9, 4, 1, 1, 16 }; // Значения y (значение погоды в градусах цельсия)
    double coef[MAX_DEGREE + 1]; // Коэффициенты полинома

    double degree = 3.3; // Степень полинома (+1)

    fractionalPolynomial(degree, x, y, coef);

    std::cout << "Polynomial coefficients: ";
    for (int i = 0; i <= degree; i++)
    {
        std::cout << coef[i] << " ";
    }
    std::cout << std::endl;

    // Использования полинома
    double future_x = x[MAX_DEGREE - 1] + 1;
    double future_y = 0;
    for (int i = 0; i <= degree; i++)
    {
        future_y += coef[i] * pow(future_x, i);
    }

    std::cout << "Given temperature: \n";
    for (int i = 0; i < MAX_DEGREE - 1; i++) {
        std::cout << testiks[i].day << '.' << testiks[i].month << '.' << testiks[i].year << ": " << y[i] << "\n";
    }
    std::cout << "Predicted temperature for " << testiks[MAX_DEGREE - 1].day << '.' << testiks[MAX_DEGREE - 1].month << '.' << testiks[MAX_DEGREE - 1].year << ": " << future_y << "\n";

    vector<double> _x, _y, _futureX, _futureY;

    for (int i = 0; i < MAX_DEGREE; i++) {
        _x.push_back(x[i]);
        _y.push_back(y[i]);
    }

    _futureX = _x;
    _futureY = _y;
    _futureX.push_back(future_x);
    _futureY.push_back(future_y);
    
    plot(_futureX, _futureY, "Future.png");
    plot(_x, _y, "Past.png");
    return 0;
}