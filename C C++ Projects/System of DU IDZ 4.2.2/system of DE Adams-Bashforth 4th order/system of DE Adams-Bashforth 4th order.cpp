// Euler 4th order
#include<iostream>
#include<cmath>
#include<iomanip>
#include<C:\Users\lxve_every1\Desktop\plots\pbPlots.hpp>
#include<C:\Users\lxve_every1\Desktop\plots\supportLib.hpp>
using namespace std;
// Defining ordinary system of differential equationes to be solved
#define dy1_dx(x, y) (1 / cosh(x + y))
#define dy2_dx(x, y) (sinh(pow(xi,2) - y))
constexpr auto h = 0.01;

double cosh_func(double x, double y)
{
	return 1 / cosh(x + y);
}

double sinh_func(double x, double y)
{
	return sinh(x * x - y);
}

double func1(double xi, double y1i) {
	double k1, k2, k3, k4, k5, k;

	// for dy1_dx
	k1 = 9 * cosh_func(xi, y1i);
	k2 = 37 * cosh_func(xi, y1i);
	k3 = 59 * cosh_func(xi, y1i);
	k4 = 55 * cosh_func(xi, y1i);
	return (h / 24) * (k4 - k3 + k2 - k1);
}

double func2(double xi, double y2i) {
	double k1, k2, k3, k4, k5, k;

	// for dy1_dx
	k1 = 9 * sinh_func(xi, y2i);
	k2 = 37 * sinh_func(xi, y2i);
	k3 = 59 * sinh_func(xi, y2i);
	k4 = 55 * sinh_func(xi, y2i);
	return (h / 24) * (k4 - k3 + k2 - k1);
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
	settings->title = toVector(L"Adams-Moulton 4th order");
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
	y1i = 2;
	y2i = 1;
	xi = 1;
	xk = 3;

	eps = 0.01;
	n = (xk - xi) / eps;

	// Calculating step size (h)
	h = eps;

	// Algorithm
	cout << setw(15) << "xi" << setw(15) << "y1i" << setw(15) << "y2i" << setw(15) << "y1k" << setw(15) << "y2k\n";
	cout << "---------------------------------------------------------------------------\n";
	for (i = 0; i < n; i++)
	{
		// for dy1_dx
		y2k = y2i + func1(xi, y2i);

		// for dy2_dx
		y1k = y1i + func2(xi, y1i);

		//if (i % 20 == 0)
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
