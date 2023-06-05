#include <iostream>
#include <cmath>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>
#include <iomanip>
using namespace std;

double func(double x, double a, double b, double k) {
    return pow(log(x), a / b) * sin(k * x);
}

/*
double diff_func(double x, double a, double b, double k) {
    double ln_x = log(x);
    return pow(ln_x, a / b - 1) * (a / b * cos(k * x) * sin(ln_x) + k * pow(ln_x, a / b) * cos(k * x));
}
*/


double diff_func(double x, double a, double b, double k) {
    return ((a * pow(log(x), (a / b) - 1) * sin(k * x)) / (b * x)) + k * pow(log(x), (a/b)) * cos(k * x);
}



double diff2_func(double x, double a, double b, double k) {
    return ((a * (pow(log(x), (a / b) - 2) * (1 - a / b) * sin(k * x) - pow(log(x), (a / b) - 1) * cos(k * x) * k * x)) / (b * x * x))
        + ((-a * pow(log(x), (a / b) - 1) * sin(k * x)) / (b * x * x))
        + ((k * (pow(log(x), (a / b)) * (-sin(k * x) * k * x + cos(k * x)) * log(x))) / x);
}


double lagrange_poly(double x, const vector<double>& xi, const vector<double>& yi, int n) {
    double L = 0;
    for (int i = 0; i < n; i++) {
        double l = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                l *= (x - xi[j]) / (xi[i] - xi[j]);
            }
        }
        L += yi[i] * l;
    }
    return L;
}

/*
double newton_poly(double x, const vector<double>& xi, const vector<double>& yi, int n) {
    double res = 0;
    for (int i = n; i >= 0; i--) {
        double prod = 1;
        for (int j = n; j > i; j--) {
            prod *= (x - xi[j]);
        }
        res += yi[i] * prod;
    }
    return res;
}
*/
double newton_poly(double x, const vector<double>& xi, const vector<double>& yi, int n) {
    double res = yi[n];
    for (int i = n - 1; i >= 0; i--) {
        res = yi[i] + (x - xi[i]) * res;
    }
    return res;
}


void plot(vector<double> x, vector<double> y, vector<double> L4, vector<double> newton_poly, const char* plotName) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* seriesXY = GetDefaultScatterPlotSeriesSettings();
    seriesXY->xs = &x;
    seriesXY->ys = &y;
    seriesXY->lineType = toVector(L"solid");
    seriesXY->pointType = toVector(L"circles");
    seriesXY->linearInterpolation = true;
    seriesXY->color = CreateRGBColor(0, 0, 0);

    ScatterPlotSeries* seriesXYCircles = GetDefaultScatterPlotSeriesSettings();
    seriesXYCircles->xs = &x;
    seriesXYCircles->ys = &y;
    seriesXYCircles->lineType = toVector(L"solid");
    seriesXYCircles->pointType = toVector(L"circles");
    seriesXYCircles->linearInterpolation = false;
    seriesXYCircles->color = CreateRGBColor(0, 0, 0);

    ScatterPlotSeries* seriesL4 = GetDefaultScatterPlotSeriesSettings();
    seriesL4->xs = &x;
    seriesL4->ys = &L4;
    seriesL4->lineType = toVector(L"solid");
    seriesL4->pointType = toVector(L"circles");
    seriesL4->linearInterpolation = true;
    seriesL4->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* seriesL4Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL4Circles->xs = &x;
    seriesL4Circles->ys = &L4;
    seriesL4Circles->lineType = toVector(L"solid");
    seriesL4Circles->pointType = toVector(L"circles");
    seriesL4Circles->linearInterpolation = false;
    seriesL4Circles->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* seriesNewton_poly = GetDefaultScatterPlotSeriesSettings();
    seriesNewton_poly->xs = &x;
    seriesNewton_poly->ys = &newton_poly;
    seriesNewton_poly->lineType = toVector(L"solid");
    seriesNewton_poly->pointType = toVector(L"circles");
    seriesNewton_poly->linearInterpolation = true;
    seriesNewton_poly->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesNewton_polyCircles = GetDefaultScatterPlotSeriesSettings();
    seriesNewton_polyCircles->xs = &x;
    seriesNewton_polyCircles->ys = &newton_poly;
    seriesNewton_polyCircles->lineType = toVector(L"solid");
    seriesNewton_polyCircles->pointType = toVector(L"circles");
    seriesNewton_polyCircles->linearInterpolation = false;
    seriesNewton_polyCircles->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Lagrange's polynom");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(seriesXY);
    settings->scatterPlotSeries->push_back(seriesXYCircles);
    settings->scatterPlotSeries->push_back(seriesL4);
    settings->scatterPlotSeries->push_back(seriesL4Circles);
    settings->scatterPlotSeries->push_back(seriesNewton_poly);
    settings->scatterPlotSeries->push_back(seriesNewton_polyCircles);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, plotName);
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    cout << setprecision(8);
    const double a = 13, b = 4, k = 3, c = 5, d = 8;
    const int m = 100, n = 2;

    double h = (d - c) / (m);

    vector<double> xi;
    vector<double> yi;
    vector<double> yi2;

    double step = (d - c) / (m);
    for (double i = c; i <= d; i += step) {
        xi.push_back(i);
        yi.push_back(diff_func(i, a, b, k));
        yi2.push_back(diff2_func(i, a, b, k));
    }

    vector<vector<double>> L(3); // вектор для многочленов порядков 2, 3, 4

    vector<double> x, y, y_diff_exact, y_diff2_exact;
    vector<vector<double>> y_diff_approx_lagrange(3), y_diff2_approx_lagrange(3);
    vector<vector<double>> y_diff_approx_newton(3), y_diff2_approx_newton(3);

    int add_degree = 2;

    double x_point = c;
    while (x_point <= d+0.01) {
        x.push_back(x_point);
        y.push_back(func(x_point, a, b, k));
        y_diff_exact.push_back(diff_func(x_point, a, b, k));
        y_diff2_exact.push_back(diff2_func(x_point, a, b, k));

        for (int i = 0; i < 3; i++) { // вычисление приближенных значений производных
            y_diff_approx_lagrange[i].push_back((lagrange_poly(x_point, xi, yi, i + add_degree)));
            y_diff2_approx_lagrange[i].push_back((lagrange_poly(x_point, xi, yi2, i + add_degree)));

            y_diff_approx_newton[i].push_back((newton_poly(x_point, xi, yi, i + add_degree)));
            y_diff2_approx_newton[i].push_back((newton_poly(x_point, xi, yi2, i + add_degree)));
        }
        x_point += h;
    }

    while (y_diff2_approx_lagrange[0].size() > 20)  
        y_diff2_approx_lagrange[0].pop_back();

    // вывод таблицы сравнения точных и приближенных значений производных
    cout << setw(5) << "x" << setw(15) << "y" << setw(15) << "y'" << setw(15) << "L4'" << setw(15) << "N4'" << setw(15) << "y''" << setw(15) << "L4''" << setw(15) << "N4''\n";
    for (int i = 0; i < x.size(); i++) {
        cout << setw(5) << x[i] << setw(15) << y[i] << setw(15) << y_diff_exact[i] << setw(15) << y_diff_approx_lagrange[2][i] << setw(15) << y_diff_approx_newton[2][i] << setw(15) << y_diff2_exact[i] << setw(15) << y_diff2_approx_lagrange[2][i] << setw(15) << y_diff2_approx_newton[2][i] << "\n";
    }
    //cout << x.size() << "\t" << y_diff2_exact.size() << "\t" << y_diff2_approx[0].size() << "\t" << y_diff2_approx[1].size() << "\t" << y_diff2_approx[2].size() << "\n";

    //for (double i = 0; i < y_diff2_exact.size(); i++) {
    //    y_diff2_exact[i] += 1.1;
    //}

    plot(x, y_diff_exact, y_diff_approx_lagrange[2], y_diff_approx_newton[2], "first degree.png");
    plot(x, y_diff2_exact, y_diff2_approx_lagrange[2], y_diff2_approx_newton[2], "second degree.png");

    /*
    for (double i = 0; i < y_diff2_exact.size(); i++) {
        cout << y_diff2_exact[i] << "\n";
    }
    */
    return 0;
}