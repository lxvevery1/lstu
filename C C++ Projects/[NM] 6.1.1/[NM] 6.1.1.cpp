#include <iostream>
#include <cmath>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>
#include <iomanip>
using namespace std;

double func(double x, double a, double b, double k) {
    return pow(x, 4) + 2 * pow(x, 3) + 4 * pow(x, 2) + 5 * x + 8;
}

double diff_func(double x, double a, double b, double k) {
    double ln_x = log(x);
    return 4 * pow(x, 3) + 6 * pow(x, 2) + 8 * x + 5;
}

double diff2_func(double x, double a, double b, double k) {
    double ln_x = log(x);
    double sin_kx = sin(k * x);
    double cos_kx = cos(k * x);
    double pow_ln_x = pow(ln_x, a / b);
    double a_b = a / b;
    return 12 * pow (x, 2) + 12 * x + 8;
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

void plot(vector<double> x, vector<double> y, vector<double> L2, vector<double> L3, vector<double> L4, const char* plotName) {

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

    ScatterPlotSeries* seriesL2 = GetDefaultScatterPlotSeriesSettings();
    seriesL2->xs = &x;
    seriesL2->ys = &L2;
    seriesL2->lineType = toVector(L"solid");
    seriesL2->pointType = toVector(L"circles");
    seriesL2->linearInterpolation = true;
    seriesL2->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* seriesL2Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL2Circles->xs = &x;
    seriesL2Circles->ys = &L2;
    seriesL2Circles->lineType = toVector(L"solid");
    seriesL2Circles->pointType = toVector(L"circles");
    seriesL2Circles->linearInterpolation = false;
    seriesL2Circles->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries* seriesL3 = GetDefaultScatterPlotSeriesSettings();
    seriesL3->xs = &x;
    seriesL3->ys = &L3;
    seriesL3->lineType = toVector(L"solid");
    seriesL3->pointType = toVector(L"circles");
    seriesL3->linearInterpolation = true;
    seriesL3->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesL3Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL3Circles->xs = &x;
    seriesL3Circles->ys = &L3;
    seriesL3Circles->lineType = toVector(L"solid");
    seriesL3Circles->pointType = toVector(L"circles");
    seriesL3Circles->linearInterpolation = false;
    seriesL3Circles->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSeries* seriesL4 = GetDefaultScatterPlotSeriesSettings();
    seriesL4->xs = &x;
    seriesL4->ys = &L4;
    seriesL4->lineType = toVector(L"solid");
    seriesL4->pointType = toVector(L"circles");
    seriesL4->linearInterpolation = true;
    seriesL4->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* seriesL4Circles = GetDefaultScatterPlotSeriesSettings();
    seriesL4Circles->xs = &x;
    seriesL4Circles->ys = &L4;
    seriesL4Circles->lineType = toVector(L"solid");
    seriesL4Circles->pointType = toVector(L"circles");
    seriesL4Circles->linearInterpolation = false;
    seriesL4Circles->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Lagrange");
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
    WriteToFile(pngData, plotName);
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    //cout << setprecision(10);
    const double a = 13, b = 4, k = 3, c = 5, d = 8;
    const int m = 20, n = 3;

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
    vector<vector<double>> y_diff_approx(3), y_diff2_approx(3);

    double x_point = c;
    while (x_point <= d) {
        x.push_back(x_point);
        y.push_back(func(x_point, a, b, k));
        y_diff_exact.push_back(diff_func(x_point, a, b, k));
        y_diff2_exact.push_back(diff2_func(x_point, a, b, k));

        for (int i = 0; i < 3; i++) { // вычисление приближенных значений производных
            y_diff_approx[i].push_back((lagrange_poly(x_point, xi, yi, i + 2)));
            
            y_diff2_approx[i].push_back((lagrange_poly(x_point, xi, yi2, i + 2)));   
        }
        x_point += h;
    }

    /*
    for (int i = 0; i < 3; i++) { // вычисление многочленов порядков 2, 3, 4
        for (double j = c; j <= d; j += h) {
            L[i].push_back(lagrange_poly(j, xi, yi, i + 2));
        }
    }
    */

    while (y_diff2_approx[0].size() > 20)
        y_diff2_approx[0].pop_back();

    // вывод таблицы сравнения точных и приближенных значений производных
    cout << setw(5) << "x" << setw(15) << "y" << setw(15) << "y'" << setw(15) << "L2'" << setw(15) << "L3'" << setw(15) << "L4'" << setw(15) << "y''" << setw(15) << "L2''" << setw(15) << "L3''" << setw(15) << "L4''\n\n";
    for (int i = 0; i < x.size(); i++) {
        cout << setw(5) << x[i] << setw(15) << y[i] << setw(15) << y_diff_exact[i] << setw(15) << y_diff_approx[0][i] << setw(15) << y_diff_approx[1][i] << setw(15) << y_diff_approx[2][i] << setw(15) << y_diff2_exact[i] << setw(15) << y_diff2_approx[0][i] << setw(15) << y_diff2_approx[1][i] << setw(15) << y_diff2_approx[2][i] << "\n";
    }
    //  cout << x.size() << "\t" << y_diff2_exact.size() << "\t" << y_diff2_approx[0].size() << "\t" << y_diff2_approx[1].size() << "\t" << y_diff2_approx[2].size() << "\n";

    //for (double i = 0; i < y_diff2_exact.size(); i++) {
    //    y_diff2_exact[i] += 1.1;
    //}

    plot(xi, y_diff_exact, y_diff_approx[0], y_diff_approx[1], y_diff_approx[2], "Lagrange_1.png");
    plot(x, y_diff2_exact, y_diff2_approx[0], y_diff2_approx[1], y_diff2_approx[2], "Lagrange_2.png");
    /*
    for (double i = 0; i < y_diff2_exact.size(); i++) {
        cout << y_diff2_exact[i] << "\n";
    }
    */
    return 0;
}