#include <iostream>
#include <cmath>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>

using namespace std;

const double a = 9, b = 7, k = 3, c = 3, d = 24, m = 8, n = 5, h = .36666666666666666666666666666667;

// функция для вычисления значения функции sin(3.14 * x)
double f(double x) {
    return pow(log(x), (a / b)) * sin(k * x); // pow(log(x), (a / b)) * sin(k * x)
}


double lagrange_poly(double x, const vector<double>& x_values, const vector<double>& y_values) {
        double result = 0.0;
        for (size_t i = 0; i < x_values.size(); ++i) {
            double term = y_values[i];
            for (size_t j = 0; j < x_values.size(); ++j) {
                if (j != i) {
                    term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
                }
            }
            result += term;
        }
        return result;
}

double lagrange_poly5(double x, const vector<double>& x_values, const vector<double>& y_values) {
    double result = 0.0;
    size_t n = x_values.size();
    if (n < 6) {
        throw std::invalid_argument("At least 6 points are required for 5th order Lagrange interpolation.");
    }
    for (size_t i = 0; i < n; ++i) {
        double term = y_values[i];
        for (size_t j = 0; j < n; ++j) {
            if (j != i) {
                term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        double w = 1.0;
        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                w *= (x - x_values[k]) / (x_values[i] - x_values[k]);
            }
        }
        result += term * (35.0 * w * w - 30.0 * w + 3.0) / 8.0;
    }
    return result;
}


// функция для построения графика
void plot(vector<double> x, vector<double> y, vector<double> x_spline, vector<double> y_spline, vector<double> x_points, vector<double> y_points) {
    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x;
    series1->ys = &y;
    series1->lineType = toVector(L"solid");
    series1->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &x_spline;
    series2->ys = &y_spline;
    series2->lineType = toVector(L"solid");
    series2->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* series3 = GetDefaultScatterPlotSeriesSettings();
    series3->xs = &x_points;
    series3->ys = &y_points;
    series3->pointType = toVector(L"circles");
    series3->linearInterpolation = false;
    series3->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Lagrange 3rd order spline");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);
    settings->scatterPlotSeries->push_back(series3);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    // задаем точки
    
    vector<double> xi;
    for (double i = c; i < d; i += h) {
        xi.push_back(i);
    }

    vector<double> yi;
    for (double x : xi) {
        yi.push_back(f(x));
    }

    // задаем значения для векторов x и y
    vector<double> x, y, x_spline, y_spline;
    double step = 0.25;

    for (double i = c; i < d; i += step)
    {
        x.push_back(i);
        y.push_back(f(i));


        x_spline.push_back(i);
        y_spline.push_back(lagrange_poly(i, xi, yi));
        
    }
    vector<double> x_points, y_points;
    for (double i = 0; i < x.size(); i += x.size() / (n * m) * 2.5) { // i += x.size() / (n*m)
        x_points.push_back(x[i]);
        y_points.push_back(y[i]);
    }
    /*
    cout << "\n-----SPLINE-----\n";
    for (int i = 0; i < x_spline.size(); i += x_spline.size() / (n * m)) {
        cout << y_spline[i] << "\n";
    }

    cout << "\n-----FUNC-----\n";
    for (int i = 0; i < x.size(); i += x.size() / (n * m)) {
        cout << y[i] << "\n";
    }

    cout << "\n-----POINTS-----\n";
    for (int i = 0; i < x_points.size(); i += x_points.size() / (n * m)) {
        cout << y_points[i] << "\n";
    }
    /*
    cout << "x_spline_size:" << x_spline.size() << "\n";
    cout << "x_func_size:" << x.size() << "\n";
    cout << "x_points_size:" << x_points.size() << "\n";
    */
    cout << "h: " << h << "\n";
    cout << "x_points_size = " << x_points.size() << "\n";

    // строим графики
    plot(x, y, x_spline, y_spline, x_points, y_points);
    return 0;
}
