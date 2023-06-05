#include <iostream>
#include <cmath>
#include <vector>
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

// Функция для построения аппроксимирующей функции по точкам
void point_approximation(vector<double> x, vector<double> y, double& a, double& b, double& mse) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += log(x[i]);
        sum_y += log(y[i]);
        sum_xy += log(x[i]) * log(y[i]);
        sum_x2 += log(x[i]) * log(x[i]);
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
    vector<double> x = { 0.034, 0.394, 0.754, 1.114, 1.474, 1.833, 2.193, 2.533, 2.913 };
    vector<double> y = { 2.156, 2.988, 3.377, 3.708, 3.802, 3.9, 4.067, 4.129, 4.171 };

    // Линейная аппроксимация
    int i;
    double a, b, mse_linear, y_pred;
    linear_approximation(x, y, a, b, mse_linear);// Аппроксимация по точкам
    double c, d, mse_point;
    point_approximation(x, y, c, d, mse_point);

    vector<double> x_approximation, y_approximation, x_points, y_points;

    // Вывод результатов
    cout << "Linear approximation:\n";
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "E = " << mse_linear << "\n";
    cout << "x\t y\t Y\n";
    for (int i = 0; i < x.size(); i++) {
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
    for (i = 0; i < x.size(); i++) {
        y_pred = c * pow(x[i], d);
        cout << x[i] << "\t " << y[i] << "\t " << y_pred << "\n";

        y_points.push_back(y_pred);
    }

    x_points = x;

    plot(x_approximation, y_approximation, x_points, y_points);
    return 0;
}