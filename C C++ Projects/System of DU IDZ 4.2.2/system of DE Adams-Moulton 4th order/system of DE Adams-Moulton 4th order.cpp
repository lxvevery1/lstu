#include<iostream>
#include<cmath>
#include<iomanip>
#include<pbPlots.hpp>
#include<supportLib.hpp>
using namespace std;
// Defining ordinary system of differential equationes to be solved
#define dy1_dx(xi, y2i) (cos(xi+y2i))
#define dy2_dx(xi, y1i) (sin(xi-y1i))
constexpr auto h = 0.01;

double cos_func(double x, double y)
{
	return 1 / cosh(x + y);
}

double sin_func(double x, double y)
{
	return sinh(x * x - y);
}

double Eul(double(*f)(double, double), double xi, double yi)
{
	return h * f(xi, yi);
}

double RK4(double(*f)(double, double), double xi, double yi) {
	double k1, k2, k3, k4, k;

	k1 = h * f(xi, yi);
	k2 = h * (f(xi + h / 2, yi + k1 / 2));
	k3 = h * (f(xi + h / 2, yi + k2 / 2));
	k4 = h * (f(xi + h, yi + k3));
	return (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

double RK5(double(*f)(double, double), double xi, double yi) {
	double k1, k2, k3, k4, k5, k;

	k1 = h * (f(xi, yi));
	k2 = h * (f(xi + h / 3, yi + k1 / 3));
	k3 = h * (f(xi + h / 3, yi + k1 / 6 + k2 / 6));
	k4 = h * (f(xi + h / 2, yi + k1 / 8 + 3 * k3 / 8));
	k5 = h * (f(xi + h, yi + k1 / 2 - (3 * k3 / 2) + 2 * k4));
	return (k1 + 4 * k4 + k5) / 6;
}

double AB4(double(*f)(double, double), double xi, double yi) {
	double k1, k2, k3, k4, k5, k;

	k1 = 9 * f(xi, yi);
	k2 = 37 * f(xi, yi);
	k3 = 59 * f(xi, yi);
	k4 = 55 * f(xi, yi);
	return (h / 24) * (k4 - k3 + k2 - k1);
}

double AM4(double(*f)(double, double), double xi, double yi) {
	double k1, k2, k3, k4, k5, k;

	k1 = f(xi, yi);
	k2 = 5 * f(xi, yi);
	k3 = 19 * f(xi, yi);
	k4 = 9 * f(xi, yi);

	return (h / 24) * (k4 + k3 - k2 + k1);
}

void DrawPlot(vector<double> x, vector<double> y1, vector<double>y2) {
	RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();

	ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
	series1->xs = &x;
	series1->ys = &y1;
	series1->linearInterpolation = false;
	series1->lineType = toVector(L"solid");
	series1->color = CreateRGBColor(0, 0, 1);

	ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &x;
	series2->ys = &y2;
	series2->linearInterpolation = false;
	series2->lineType = toVector(L"solid");
	series2->color = CreateRGBColor(0, 1, 0);

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 800;
	settings->height = 480;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"");
	settings->xLabel = toVector(L"x");
	settings->yLabel = toVector(L"y");
	settings->scatterPlotSeries->push_back(series1);
	settings->scatterPlotSeries->push_back(series2);

	DrawScatterPlotFromSettings(imageRef, settings, NULL);

	vector<double>* pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "plot.png");
	DeleteImage(imageRef->image);
}

int main()
{
	double xi, y1i, y2i, xk, h, y1k, y2k, eps;
	int i, n;
	vector<double> plot_x, plot_y1, plot_y2;
	y1i = 0.5;
	y2i = -0.5;
	xi = 0;
	xk = 8;

	eps = 0.001;
	n = (xk - xi) / eps;

	// Calculating step size (h)
	h = eps;

	// Algorithm
	cout << setw(15) << "xi" << setw(15) << "y1i" << setw(15) << "y2i" << setw(15) << "y1k" << setw(15) << "y2k\n";
	cout << "---------------------------------------------------------------------------\n";
	for (i = 0; i < n; i++)
	{
		// for dy1_dx
		y2k = y2i + AM4(cos_func, xi, y2i); //Любой другой метод

		// for dy2_dx
		y1k = y1i + AM4(sin_func, xi, y1i); //Любой другой метод

		if (i % 100 == 0)
		cout << setw(15) << xi << setw(15) << y1i << setw(15) << y2i << setw(15) << y1k << setw(15) << y2k << endl;

		plot_x.push_back(xi);
		plot_y1.push_back(y1i);
		plot_y2.push_back(y2i);

		xi += h;
		y1i = y1k;
		y2i = y2k;
	}
	// Displaying result
	cout << "\nValue of y1, y2 at x = " << xk << " is " << y1k << " , " << y2k;
	DrawPlot(plot_x, plot_y1, plot_y2);

	return 0;
}
