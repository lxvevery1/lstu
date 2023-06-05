#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <pbPlots.cpp>
#include <supportLib.cpp>

using namespace std;

// Define constants
const double a = 9;
const double b = 7;
const double k = 3;
const double c = 1;
const double d = 5;
const double m = 8;
const double n = 5;
const double ___y0 = 0.5;

const double h = (d - c) / m;

// Define the function to be differentiated
double f(double x, double y) {
    return pow(y, 2) * log(x) / x - y / x;
}

// Define the Euler method
void euler(vector<double>& x, vector<double>& y) {
    double xn = c;
    double yn = ___y0; // Replace with your initial value
    x.clear();
    x.push_back(xn);
    y.push_back(yn);

    for (int i = 0; i <= m; i++) {
        double yn1 = yn + h * f(xn, yn);
        xn += h;
        yn = yn1;
        x.push_back(xn);
        y.push_back(yn);
    }
}

// Define the improved Euler method
void improved_euler(vector<double>& x, vector<double>& y) {
    double xn = c;
    double yn = ___y0; // Replace with your initial value
    x.clear();
    x.push_back(xn);
    y.push_back(yn);

    for (int i = 0; i <= m; i++) {
        double k1 = f(xn, yn);
        double k2 = f(xn + h, yn + h * k1);
        double yn1 = yn + h * (k1 + k2) / 2;
        xn += h;
        yn = yn1;
        x.push_back(xn);
        y.push_back(yn);
    }
}

// Define the Runge-Kutta 4th order method
void runge_kutta_4(vector<double>& x, vector<double>& y) {
    double xn = c;
    double yn = ___y0;
    x.clear();
    x.push_back(xn);
    y.push_back(yn);

    for (int i = 0; i < m; i++) {
        double k1 = f(xn, yn);
        double k2 = f(xn + h / 2, yn + h * k1 / 2);
        double k3 = f(xn + h / 2, yn + h * k2 / 2);
        double k4 = f(xn + h, yn + h * k3);
        double yn1 = yn + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        xn += h;
        yn = yn1;
        x.push_back(xn);
        y.push_back(yn);
    }
}

// Define the Runge-Kutta5th order method
void runge_kutta_5(vector<double>& x, vector<double>& y) {
    double xn = c;
    double yn = ___y0;

    x.push_back(xn);
    y.push_back(yn);

    for (int i = 0; i < m; i++) {
        double k1 = f(xn, yn);
        double k2 = f(xn + h / 4, yn + h * k1 / 4);
        double k3 = f(xn + h / 4, yn + h * (k1 / 8 + k2 / 8));
        double k4 = f(xn + h / 2, yn - h * (k2 / 2) + h * k3);
        double k5 = f(xn + 3 * h / 4, yn + h * (k1 * 3 / 16 + k4 * 9 / 16));
        double k6 = f(xn + h, yn + h * (-k1 * 3 / 7 + k2 * 2 / 7 + k3 * 12 / 7 - k4 * 12 / 7 + k5 * 8 / 7));
        double yn1 = yn + h * (k1 * 7 / 90 + k3 * 32 / 90 + k4 * 12 / 90 + k5 * 32 / 90 + k6 * 7 / 90);
        xn += h;
        yn = yn1;
        x.push_back(xn);
        y.push_back(yn);
    }
}

// Define the Adams-Bashforth 4th order method
void adams_bashforth_4(vector<double>& x, vector<double>& y) {
    // Create vectors to store previous values
    vector<double> x_prev;
    vector<double> y_prev;

    x.clear();
    // Use Runge-Kutta 4th order method to calculate initial values
    runge_kutta_4(x_prev, y_prev);

    // Copy initial values to x and y vectors
    x = x_prev;
    y = y_prev;

    // Update x vector with initial values
    for (int i = 0; i < 4; i++) {
        y.push_back(y_prev[i]);
    }

    // Iterate using the Adams-Bashforth 4th order method
    for (int i = 4; i < m; i++) {
        double yn = y[i - 1] + h * (55 * f(x[i], y[i - 1]) - 59 * f(x[i - 2], y[i - 2]) + 37 * f(x[i - 3], y[i - 3]) - 9 * f(x[i - 4], y[i - 4])) / 24;
        double xn = x[i - 1] + h;
        x.push_back(xn);
        y.push_back(yn);
    }
}

// Define the Adams-Moulton 4th order method
void adams_moulton_4(vector<double>& x, vector<double>& y) {
    // Create vectors to store previous values
    vector<double> x_prev;
    vector<double> y_prev;

    x.clear();
    // Use Runge-Kutta 4th order method to calculate initial values
    runge_kutta_4(x_prev, y_prev);

    // Copy initial values to x and y vectors
    x = x_prev;
    y = y_prev;

    // Iterate using the Adams-Moulton 4th order method
    for (int i = 3; i < m; i++) {
        double yn = y[i - 1] + h * (9 * f(x[i], y[i]) + 19 * f(x[i - 1], y[i - 1]) - 5 * f(x[i - 2], y[i - 2]) + f(x[i - 3], y[i - 3])) / 24;
        double xn = x[i - 1] + h;
        x.push_back(xn);
        y.push_back(yn);
    }
}

void table(vector<double> x, vector<double> y, string method) {
    cout << "Method: " << method << endl;
    cout << setw(10) << "x" << setw(20) << "Result" << endl;
    for (int i = 0; i <= m; i++) {
        cout << setw(10) << x[i] << setw(20) << y[i] << endl;
    }
    cout << endl;
}

void def_func(vector<double>& xs, vector<double>& ys) {
    // Определяем начальное условие
    double y0 = ___y0;

    // Определяем шаг
    double h = (d - c) / m;

    xs.clear();
    ys.clear();

    // Заполняем векторы
    for (double x = c; x <= d; x += h) {
        double y = f(x, y0);
        xs.push_back(x);
        ys.push_back(abs(y));
        y0 = y; // Обновляем y0 для следующей итерации
    }
}

void plot(vector<double> x, vector<double> y, vector<double> leftRes, vector<double> rightRes, vector<double> middleRes, vector<double> trapRes, vector<double> simpRes) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* seriesXY = GetDefaultScatterPlotSeriesSettings();
    seriesXY->xs = &x;
    seriesXY->ys = &y;
    seriesXY->lineType = toVector(L"solid");
    seriesXY->pointType = toVector(L"circles");
    seriesXY->linearInterpolation = true;
    seriesXY->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* seriesLeftRes = GetDefaultScatterPlotSeriesSettings();
    seriesLeftRes->xs = &x;
    seriesLeftRes->ys = &leftRes;
    seriesLeftRes->lineType = toVector(L"solid");
    seriesLeftRes->pointType = toVector(L"circles");
    seriesLeftRes->linearInterpolation = true;
    seriesLeftRes->color = CreateRGBColor(1, 0, 1);

    ScatterPlotSeries* seriesRightRes = GetDefaultScatterPlotSeriesSettings();
    seriesRightRes->xs = &x;
    seriesRightRes->ys = &rightRes;
    seriesRightRes->lineType = toVector(L"solid");
    seriesRightRes->pointType = toVector(L"circles");
    seriesRightRes->linearInterpolation = true;
    seriesRightRes->color = CreateRGBColor(1, 0, 1);

    ScatterPlotSeries* seriesMiddleRes = GetDefaultScatterPlotSeriesSettings();
    seriesMiddleRes->xs = &x;
    seriesMiddleRes->ys = &middleRes;
    seriesMiddleRes->lineType = toVector(L"solid");
    seriesMiddleRes->pointType = toVector(L"circles");
    seriesMiddleRes->linearInterpolation = true;
    seriesMiddleRes->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* seriesTrapRes = GetDefaultScatterPlotSeriesSettings();
    seriesTrapRes->xs = &x;
    seriesTrapRes->ys = &trapRes;
    seriesTrapRes->lineType = toVector(L"solid");
    seriesTrapRes->pointType = toVector(L"circles");
    seriesTrapRes->linearInterpolation = true;
    seriesTrapRes->color = CreateRGBColor(1, 0, 1);

    ScatterPlotSeries* seriesSimpRes = GetDefaultScatterPlotSeriesSettings();
    seriesSimpRes->xs = &x;
    seriesSimpRes->ys = &simpRes;
    seriesSimpRes->lineType = toVector(L"solid");
    seriesSimpRes->pointType = toVector(L"circles");
    seriesSimpRes->linearInterpolation = true;
    seriesSimpRes->color = CreateRGBColor(1, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Integration methods comparison");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");

    vector<ScatterPlotSeries*> series({ seriesXY, seriesLeftRes, seriesRightRes, seriesMiddleRes, seriesTrapRes, seriesSimpRes });

    for (int i = 0; i < series.size(); i++) {
        settings->scatterPlotSeries->push_back(series[i]);
    }

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    vector<double> x, y;
    vector<double> eul, impEul, rk4, rk5, ab4, am4;

    def_func(x, y);
    euler(x, eul);
    improved_euler(x, impEul);
    runge_kutta_4(x, rk4);
    runge_kutta_5(x, rk5);
    adams_bashforth_4(x, ab4);
    adams_moulton_4(x, am4);

    while (x.size() > 9)
        x.pop_back();
    while (eul.size() > 9)
        eul.pop_back();
    while (rk4.size() > 9)
        rk4.pop_back();
    while (rk5.size() > 9)
        rk5.pop_back();
    while (ab4.size() > 9)
        ab4.pop_back();
    while (am4.size() > 9)
        am4.pop_back();

    table(x, y, "default func");
    table(x, eul, "euler");
    table(x, impEul, "improved_euler");
    table(x, rk4, "runge_kutta_4");
    table(x, rk5, "runge_kutta_5");
    table(x, ab4, "adams_bashforth_4");
    table(x, am4, "adams_moulton_4");


    /*for (int i = 0; i < x.size(); i++)
        cout << x[i] << "\n";*/


    cout << x.size() << "\n";
    cout << y.size() << "\n";
    cout << eul.size() << "\n";
    cout << rk4.size() << "\n";
    cout << rk5.size() << "\n";
    cout << ab4.size() << "\n";
    cout << am4.size() << "\n";


    plot(x, y, eul, rk4, rk5, ab4, am4);
}