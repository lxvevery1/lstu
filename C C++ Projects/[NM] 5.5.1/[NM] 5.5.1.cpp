#include <iostream>
#include <cmath>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>
const double a = 9, b = 7, k = 3, c = 3, d = 24, m = 8, n = 5;
using namespace std;

double f(double x) {
    return pow(log(x), (a / b)) * sin(k * x);
}


// функция для вычисления значения кубического сплайна в заданной точке по равномерной сетке
double cubic_poly(double x, const vector<double>& x_values, const vector<double>& y_values) {
    int n = x_values.size() - 1;
    int i = 0;
    while (i < n - 1 && x_values[i] < x) {
        i++;
    }
    if (i == 0) {
        return y_values[0] + (y_values[1] - y_values[0]) / (x_values[1] - x_values[0]) * (x - x_values[0]);
    }
    else if (i == n) {
        return y_values[n] + (y_values[n] - y_values[n - 1]) / (x_values[n] - x_values[n - 1]) * (x - x_values[n]);
    }
    else {
        double h = x_values[i] - x_values[i - 1];
        double a = (y_values[i] - y_values[i - 1]) / h;
        double b = (y_values[i + 1] - y_values[i]) / h;
        double c = (b - a) / (2 * h);
        double d = a + h * c;
        return y_values[i] + (x - x_values[i]) * (d + (x - x_values[i]) * (c + (x - x_values[i]) * b));
    }
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
    settings->title = toVector(L"Cubic spline");
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
    double N = n * m, h = 0.1;
    // задаем точки

    vector<double> xi;
    for (double i = c; i <= d; i += h) {
        xi.push_back(i);
    }

    vector<double> yi;
    for (double x : xi) {
        yi.push_back(f(x));
    }

    // задаем значения для векторов x и y
    vector<double> x, y, x_spline, y_spline;
    double step = h;

    for (double i = c; i <= d; i += step) {
        x.push_back(i);
        y.push_back(f(i));
    }
    for (double i = c; i <= d; i += step * 4){
        x_spline.push_back(i);
        y_spline.push_back(cubic_poly(i, xi, yi));
    }
    vector<double> x_points, y_points;
    for (double i = c; i <= d; i += 0.53 * 4) {
        x_points.push_back(i);
        y_points.push_back(cubic_poly(i, xi, yi));
    }
    cout << x_points.size();
    /*
    cout << "\n-----SPLINE-----\n";
    for (int i = 0; i < x_spline.size(); i++) {
        cout << y_spline[i] << "\n";
    }

    cout << "\n-----FUNC-----\n";
    for (int i = 0; i < x.size(); i++) {
        cout << y[i] << "\n";
    }

    cout << "\n-----POINTS-----\n";
    for (int i = 0; i < x_points.size(); i++) {
        cout << y_points[i] << "\n";
    }
    */
    // строим графики
    plot(x, y, x_spline, y_spline, x_points, y_points);
    return 0;
}
