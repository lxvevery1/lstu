#include "pbPlots.cpp"
#include "supportLib.cpp"
#include <vector>
#include <cmath>
#include <iomanip>
// Определяем функцию, которую необходимо интегрировать
double func(double x, double a, double b, double k, double d, double m, double n) {
    return pow(-1, int(x)) * b + k * a * pow(x, 2) + d * pow(x, 2) + m * x + n;
}

void plot(vector<double> x, vector<double> y) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x;
    series1->ys = &y;
    series1->lineType = toVector(L"solid");
    series1->pointType = toVector(L"circles");
    series1->linearInterpolation = true;
    series1->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Lagrange's polynom");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    // Определяем параметры задачи Коши
    double a = 9;
    double b = 7;
    double k = 3;
    double c = 3;
    double d = 24;
    double m = 8;
    double n = 5;

    // Определяем начальное условие
    double y0 = 1;

    // Определяем функцию, которая решает задачу Коши аналитически
    auto y = [&](double x) {
        return (-1) * pow(-1, int(x)) * b / k + pow(x, 2) * (a * k / 2 + d) + x * (m + (-1) * pow(-1, int(x)) * b / k) + n;
    };

    // Определяем шаг
    double h = (d-c) / m;

    // Создаем векторы для хранения координат точек
    std::vector<double> xs;
    std::vector<double> ys;

    // Заполняем векторы
    for (double x = c; x <= d; x += h) {
        xs.push_back(x);
        ys.push_back(y(x));
        cout << setw(10) << x << setw(15) << y(x) <<  "\n";
    }
    
    plot(xs, ys);

    return 0;
}
