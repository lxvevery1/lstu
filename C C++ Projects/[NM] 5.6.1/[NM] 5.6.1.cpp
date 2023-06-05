#include <iostream>
#include <pbPlots.cpp>
#include <supportLib.cpp>

using namespace std;

// Функция для построения линейной аппроксимирующей функции
void linear_approximation(vector<double> x, vector<double> y, double& a, double& b, double& mse) {
    int n = x.size();
    double sx = 0, sy = 0, sxy = 0, sx2 = 0;

    for (int i = 0; i < n; i++) {
        sx += x[i];
        sy += y[i];
        sxy += x[i] * y[i];
        sx2 += x[i] * x[i];
    }

    double det = n * sx2 - sx * sx;
    a = (sy * sx2 - sx * sxy) / det;
    b = (n * sxy - sx * sy) / det;

    // Вычисление среднеквадратической ошибки
    mse = 0;
    for (int i = 0; i < n; i++) {
        double y_pred = a + b * x[i];
        mse += (y[i] - y_pred) * (y[i] - y_pred);
    }
    mse = sqrt(mse / n);
}

void point_approximation(vector<double> x, vector<double> y, double& a, double& b, double& mse) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        double log_x = log(x[i] < 0 ? -x[i] : x[i]);
        double log_y = log(y[i] < 0 ? -y[i] : y[i]);
        if (x[i] < 0) log_x *= -1;
        if (y[i] < 0) log_y *= -1;
        sum_x += log_x;
        sum_y += log_y;
        sum_xy += log_x * log_y;
        sum_x2 += log_x * log_x;
    }

    b = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    a = exp((sum_y - b * sum_x) / n);

    // Вычисление среднеквадратической ошибки
    mse = 0;
    for (int i = 0; i < n; i++) {
        double y_pred = a * pow(x[i], b);
        mse += (y[i] - y_pred) * (y[i] - y_pred);
    }
    mse = sqrt(mse / n);
}

// функция для построения графика
void plot(vector<double> x_approximation, vector<double> y_approximation, vector<double> x_points, vector<double> y_points) {
    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x_approximation;
    series1->ys = &y_approximation;
    series1->lineType = toVector(L"solid");
    series1->color = CreateRGBColor(0, 0, 1);


    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &x_points;
    series2->ys = &y_points;
    series2->pointType = toVector(L"circles");
    series2->linearInterpolation = false;
    series2->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Approximation");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    //vector<double> x = { 0.259, 0.597, 0.934, 1.272, 1.610, 1.948, 2.286, 2.623, 2.961 };
    //vector<double> y = { 0.018, -0.920, -1.516, -1.647, -1.586, -1.328, -0.573, 0.172, 1.122 };

    vector<double> x = { 0.034, 0.394, 0.754, 1.114, 1.474, 1.833, 2.193, 2.533, 2.913 };
    vector<double> y = { 2.156, 2.988, 3.377, 3.708, 3.802, 3.9, 4.067, 4.129, 4.171 };

    //vector<double> x = { 0.135, 0.482, 0.829, 1.176, 1.523, 1.869, 2.216, 2.563, 2.910 };
    //vector<double> y = { -0.642, -0.235, -0.111, -0.057, 0.032, -0.002, -0.237, -0.323, -0.449 };

    // Линейная аппроксимация
    int i;
    double a, b, mse_linear, y_pred;
    linear_approximation(x, y, a, b, mse_linear);  // Аппроксимация по точкам
    double c, d, mse_point;
    point_approximation(x, y, c, d, mse_point);

    vector<double> x_approximation, y_approximation, x_points, y_points;

    // Вывод результатов
    cout << "Linear approximation:\n";
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "E = " << mse_linear << "\n";
    cout << "x\t y\t Y\n";
    for (i = 0; i < x.size(); i++) {
        double y_pred = a + b * x[i];
        cout << x[i] << "\t " << y[i] << "\t " << y_pred << "\n";

        y_approximation.push_back(y_pred);
    }

    x_approximation = x;

    cout << "\n";
    cout << "Point approximation:\n";
    cout << "c = " << c << "\n";
    cout << "d = " << d << "\n";
    cout << "E = " << mse_point << "\n";
    cout << "x\t y\t Y\n";
    bool negativeness = false;
    for (int i = 0; i < y.size(); i++) {
        if (y[i] < 0.0) {
            negativeness = true;
        }
    }
    //negativeness = false;

    
    switch (negativeness) {
    case 0:
        for (i = 0; i < x.size(); i++) {
            y_pred = c * pow(x[i], d);
            cout << x[i] << "\t " << y[i] << "\t " << y_pred << "\n";
            y_points.push_back(y_pred);
        }
        break;
    case 1:
        for (i = 0; i < x.size(); i++) {
            y_pred = c * pow(x[i], d);
            cout << x[i] << "\t " << y[i] << "\t " << y_pred << "\n";
            y_points.push_back(y_pred);
        }
        cout << "Negativeness detected\n";
        double y_penalty = abs(y_approximation[y_approximation.size() / 2] - y_points[y_points.size() / 2]);
        y_points.clear();
        for (i = 0; i < x.size(); i++) {
            y_pred = c * pow(x[i], d) - y_penalty;
            cout << x[i] << "\t " << y[i] << "\t " << y_pred << "\n";
            y_points.push_back(y_pred);
        }
        break;
    }
    
    x_points = x;

    plot(x_approximation, y_approximation, x_points, y_points);
    return 0;
}