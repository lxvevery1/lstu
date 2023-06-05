#include <iostream>
#include <cmath>
#include <iomanip>
#include <pbPlots.cpp>
#include <supportLib.cpp>
using namespace std;

double f(double x) {
    return 0.5 * exp(-sqrt(x)) - 0.2 * sqrt(pow(x, 3)) + 2;
}
double df(double x) {
    return (-0.25 * exp(-sqrt(x))) / sqrt(x) - 0.3 * sqrt(x);
}
double phi(double x) {
    return -2/(0.5 * exp(-sqrt(x)) - 0.2 * sqrt(pow(x,3)));
}
double phi_test(double x) {
    return x - ((1.0/df(x))*(f(x)));
}

// Для графического представления функций разделим нашу f на f1 и f2
double f1(double x) {
    return 0.5 * exp(-sqrt(x));
}
double f2(double x) {
    return - 0.2 * sqrt(pow(x,3)) + 2;
}

double dichotomy(double a, double b, double eps) {
    int ticks = 0;
    while (b - a >= eps) {
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        ticks++;
    }
    cout << "Number of dichotomy method ticks: " << ticks;
    return (a + b) / 2;
}

double newton(double x, double eps) {
    double x_next = x - f(x) / df(x);
    int ticks = 0;
    while (abs(x_next - x) >= eps) {
        x = x_next;
        x_next = x - f(x) / df(x);
        ticks++;
    }
    cout << "\nNumber of Newton's method ticks: " << ticks;
    return x_next;
}

double simple_iteration(double x0, double eps) {
    double x1 = phi_test(x0);
    int ticks = 0;
    while (fabs(x1 - x0) > eps) {
        x0 = x1;
        x1 = phi_test(x0);
        ticks++;
    }
    cout << "\nNumber of simple iteration method ticks: " << ticks;
    return x1;
}

double steffensen(double x, double eps) {
    double x0, x1 = x, fpx;
    int ticks = 0;
    do {
        x0 = x1;
        fpx = (f(x0 + f(x0)) - f(x0));
        x1 = x0 - (pow(f(x0),2)) / fpx;

        ticks++;
    } while (abs(f(x1)) > eps);
    cout << "\nNumber of ticks: " << ticks;
    return x0;
}

int main() {
    cout << setprecision(7) << fixed;
    double eps = 1e-6;
    double a = 0;
    double b = 5;

    double dihRoot = dichotomy(a, b, eps);
    cout << "\nDichotomy root = " << dihRoot << "\n";

    double newtRoot = newton((b-a)/2, eps);
    cout << "\nNewton root = " << newtRoot << "\n";

    double simpleIterRoot = simple_iteration(b, eps); // where 1st argument is x0
    cout << "\nSimple iteration root = " << simpleIterRoot << "\n";

    double steffensenRoot = steffensen((b-a)/2, eps); // where 1st argument is x0
    cout << "\nSteffensen's method root = " << steffensenRoot << "\n";

#pragma region Plot

    vector<double> f1_array;
    vector<double> f2_array;
    vector<double> x_array;
    double temp = a;
    while (temp <= b) {
        x_array.push_back(temp);
        f1_array.push_back(f1(temp));
        f2_array.push_back(f2(temp));
        temp += 0.1;
    }

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x_array;
    series1->ys = &f1_array;
    series1->lineType = toVector(L"solid");
    series1->color = CreateRGBColor(0, 0, 1);
    

    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &x_array;
    series2->ys = &f2_array;
    series2->lineType = toVector(L"solid");
    series2->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"0.5 * exp(-sqrt(x)) - 0.2 * sqrt(pow(x, 3)) + 2");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);
 
    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);

#pragma endregion

    return 0;
}