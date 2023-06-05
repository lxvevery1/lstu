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

double diff_func(double x, double a, double b, double k) {
    double ln_x = log(x);
    return pow(ln_x, a / b - 1) * (a / b * cos(k * x) * sin(ln_x) + k * pow(ln_x, a / b) * cos(k * x));
}

double diff2_func(double x, double a, double b, double k) {
    double ln_x = log(x);
    double sin_kx = sin(k * x);
    double cos_kx = cos(k * x);
    double pow_ln_x = pow(ln_x, a / b);
    double a_b = a / b;
    return pow_ln_x * (pow_ln_x * cos_kx - 2 * a_b * ln_x * sin_kx) + 2 * a_b * cos_kx * sin(ln_x);
}

double backward_difference(int n, const vector<double>& y) {
    if (n >= y.size()) {
        return 0;
    }
    double res = y[n];
    int i = 1;
    while (n - i >= 0) {
        res -= y[n - i];
        i++;
    }
    return res;
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

void plot(vector<double> x, vector<double> y, vector<double> L2, vector<double> L3, vector<double> L4) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* seriesXY = GetDefaultScatterPlotSeriesSettings();
    seriesXY->xs = &x;
    seriesXY->ys = &y;
    seriesXY->lineType = toVector(L"solid");
    seriesXY->pointType = toVector(L"circles");
    seriesXY->linearInterpolation = true;
    seriesXY->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* seriesXYCircles = GetDefaultScatterPlotSeriesSettings();
    seriesXYCircles->xs = &x;
    seriesXYCircles->ys = &y;
    seriesXYCircles->lineType = toVector(L"solid");
    seriesXYCircles->pointType = toVector(L"circles");
    seriesXYCircles->linearInterpolation = false;
    seriesXYCircles->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* seriesL2 = GetDefaultScatterPlotSeriesSettings();
    seriesL2->xs = &x;
    seriesL2->ys = &L2;
    seriesL2->lineType = toVector(L"solid");
    seriesL2->pointType = toVector(L"circles");
    seriesL2->linearInterpolation = true;
    seriesL2->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesL2Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL2Circles->xs = &x;
    seriesL2Circles->ys = &L2;
    seriesL2Circles->lineType = toVector(L"solid");
    seriesL2Circles->pointType = toVector(L"circles");
    seriesL2Circles->linearInterpolation = false;
    seriesL2Circles->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesL3 = GetDefaultScatterPlotSeriesSettings();
    seriesL3->xs = &x;
    seriesL3->ys = &L3;
    seriesL3->lineType = toVector(L"solid");
    seriesL3->pointType = toVector(L"circles");
    seriesL3->linearInterpolation = true;
    seriesL3->color = CreateRGBColor(1, 0, 0);
    
    ScatterPlotSeries* seriesL3Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL3Circles->xs = &x;
    seriesL3Circles->ys = &L3;
    seriesL3Circles->lineType = toVector(L"solid");
    seriesL3Circles->pointType = toVector(L"circles");
    seriesL3Circles->linearInterpolation = false;
    seriesL3Circles->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* seriesL4 = GetDefaultScatterPlotSeriesSettings();
    seriesL4->xs = &x;
    seriesL4->ys = &L4;
    seriesL4->lineType = toVector(L"solid");
    seriesL4->pointType = toVector(L"circles");
    seriesL4->linearInterpolation = true;
    seriesL4->color = CreateRGBColor(1, 1, 0);

    ScatterPlotSeries* seriesL4Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL4Circles->xs = &x;
    seriesL4Circles->ys = &L4;
    seriesL4Circles->lineType = toVector(L"solid");
    seriesL4Circles->pointType = toVector(L"circles");
    seriesL4Circles->linearInterpolation = false;
    seriesL4Circles->color = CreateRGBColor(1, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Backward interpolation");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(seriesXY);
    settings->scatterPlotSeries->push_back(seriesXYCircles);
    settings->scatterPlotSeries->push_back(seriesL2);
    settings->scatterPlotSeries->push_back(seriesL2Circles);
    settings->scatterPlotSeries->push_back(seriesL3);
    settings->scatterPlotSeries->push_back(seriesL3Circles);
    settings->scatterPlotSeries->push_back(seriesL4);
    settings->scatterPlotSeries->push_back(seriesL4Circles);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    const double a = 9, b = 7, k = 3, c = 3, d = 24; // d = 5
    const int m = 8;
    double h = (d - c) / (m);

    vector<double> xi;
    vector<double> yi;

    double step = (d - c) / (m);

    for (double i = c; i <= d; i += step) {
        xi.push_back(i);
        yi.push_back(func(i, a, b, k));
    }

    vector<vector<double>> L(3);

    vector<double> x, y, y_diff_exact, y_diff2_exact;
    vector<vector<double>> y_diff_approx(3), y_diff2_approx(3);

    double x_point = c;
    while (x_point <= d) {
        x.push_back(x_point);
        y.push_back(func(x_point, a, b, k));
        y_diff_exact.push_back(diff_func(x_point, a, b, k));
        y_diff2_exact.push_back(diff2_func(x_point, a, b, k));

        for (int i = 0; i < 3; i++) {
            y_diff_approx[i].push_back(backward_difference(i, yi));
            y_diff2_approx[i].push_back(backward_difference(i, y_diff_approx[i]));
        }

        x_point += step;
    }

    for (int i = 0; i < 3; i++) { // вычисление многочленов порядков 2, 3, 4
        for (double j = c; j <= d; j += h) {
            L[i].push_back(lagrange_poly(j, xi, yi, i + 2));
        }
    }

    //plot(x, y, L[0], L[1], L[2]);

    cout << "Exact values of derivatives:" << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << "x = " << x[i] << ", y' = " << y_diff_exact[i] << ", y'' = " << y_diff2_exact[i]
            << endl;
    }

    cout << "Approximate values of derivatives:" << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << "x = " << x[i] << ", N'2 = " << y_diff_approx[0][i] << ", N'3 = " << y_diff_approx[1][i]
            << ", N'4 = " << y_diff_approx[2][i] << ", N''2 = " << y_diff2_approx[0][i] << ", N''3 = "
            << y_diff2_approx[1][i] << ", N''4 = " << y_diff2_approx[2][i] << endl;
    }

    plot(x, y, L[0], L[1], L[2]);

    return 0;
}