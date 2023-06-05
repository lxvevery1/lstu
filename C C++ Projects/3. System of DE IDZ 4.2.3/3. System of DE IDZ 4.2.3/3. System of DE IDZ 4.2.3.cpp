#include<iostream>
#include<iomanip>
#include<pbPlots.cpp>
#include<supportLib.cpp>

using namespace std;
#define exp 2.7182818284
constexpr auto h = 0.01;
// Defining ordinary system of differential equationes to be solved
#define f1(xi, y1i, y2i, y3i) cos(y1i * y2i * y3i)
#define f2(xi, y1i, y2i, y3i) pow(exp, (xi*y1i*y3i))
#define f3(xi, y1i, y2i, y3i) sin(y1i * y2i * y3i)

#define f1 -y2i + sin(xi * y3i)
#define f2 pow(y1i, 2)
#define f3 -y3i - y1i

double epow_func(double xi, double y1i, double y2i, double y3i)
{
	return pow(exp, y3i-y1i);
}

double sin_func(double xi, double y1i, double y2i, double y3i)
{
	return sin(xi * y3i);
}

double sqrt_func(double xi, double y1i, double y2i, double y3i)
{
	return sqrt(pow(xi, 2) + pow(y1i, 2) + pow(y2i, 2));
}

double Eul(double (*f) (double, double, double, double), double xi, double y1i, double y2i, double y3i) {
	return h * f(xi, y1i, y2i, y3i);
}

double RK4(double (*f) (double, double, double, double), double xi, double y1i, double y2i, double y3i)
{
	double k1 = h * f(xi, y1i, y2i, y3i);
	double k2 = h * f(xi + h / 2, y1i + k1 / 2, y2i + k1 / 2, y3i + k1 / 2);
	double k3 = h * f(xi + h / 2, y1i + k2 / 2, y2i + k2 / 2, y3i + k2 / 2);
	double k4 = h * f(xi + h, y1i + k3, y2i + k3, y3i + k3);
	return (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

double RK5(double (*f) (double, double, double, double), double xi, double y1i, double y2i, double y3i)
{
	double k1, k2, k3, k4, k5, k;
	k1 = h * (f(xi, y1i, y2i, y3i));
	k2 = h * (f(xi + h / 3, y1i + k1 / 3, y2i + k1 / 3, y3i + k1 / 3));
	k3 = h * (f(xi + h / 3, y1i + k1 / 6 + k2 / 6, y2i + k1 / 6 + k2 / 6, y3i + k1 / 6 + k2 / 6));
	k4 = h * (f(xi + h / 2, y1i + k1 / 8 + 3 * k3 / 8, y2i + k1 / 8 + 3 * k3 / 8, y3i + k1 / 8 + 3 * k3 / 8));
	k5 = h * (f(xi + h, y1i + k1 / 2 - (3 * k3 / 2) + 2 * k4, y2i + k1 / 2 - (3 * k3 / 2) + 2 * k4, y3i + k1 / 2 - (3 * k3 / 2) + 2 * k4));
	k = (k1 + 4 * k4 + k5) / 6;
	return k;
}

double AB4(double (*f) (double, double, double, double), double xi, double y1i, double y2i, double y3i)
{
	double k1, k2, k3, k4, k;
	k1 = f(xi, y1i, y2i, y3i);
	k2 = 5 * f(xi, y1i, y2i, y3i);
	k3 = 19 * f(xi, y1i, y2i, y3i);
	k4 = 9 * f(xi, y1i, y2i, y3i);
	k = (h / 24) * (k4 + k3 - k2 + k1);
	return k;
}

double AM4(double (*f) (double, double, double, double), double xi, double y1i, double y2i, double y3i)
{
	double k1, k2, k3, k4, k;
	k1 = 9 * f(xi, y1i, y2i, y3i);
	k2 = 37 * f(xi, y1i, y2i, y3i);
	k3 = 59 * f(xi, y1i, y2i, y3i);
	k4 = 55 * f(xi, y1i, y2i, y3i);
	k = (h / 24) * (k4 - k3 + k2 - k1);
	return k;
}

void DrawPlot(vector<double> x, vector<double> y1, vector<double>y2, vector<double>y3) {
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

	ScatterPlotSeries* series3 = GetDefaultScatterPlotSeriesSettings();
	series3->xs = &x;
	series3->ys = &y3;
	series3->linearInterpolation = false;
	series3->lineType = toVector(L"solid");
	series3->color = CreateRGBColor(1, 0, 0);

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
	settings->scatterPlotSeries->push_back(series3);

	DrawScatterPlotFromSettings(imageRef, settings, NULL);

	vector<double>* pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "plot.png");
	DeleteImage(imageRef->image);
}

int main()
{
	double xi, y1i, y2i, y3i, xk, h, y1k, y2k, y3k, eps,
		ky1, ky2, ky3;
	vector<double> plot_x, plot_y1, plot_y2, plot_y3;
	int i, n;

	y1i = 2;
	y2i = -1;
	y3i = 0;

	xi = 1;
	xk = 3;

	eps = 0.01;
	n = (xk - xi) / eps;
	// Calculating step size (h)
	h = eps;

	// Algorithm
	cout << setw(10) << "xi" << setw(10) << "y1i" << setw(10) << "y2i" << setw(10) << "y3i" << setw(10) << "y1k" << setw(10) << setw(10) << "y2k" << setw(10) << "y3k\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	for (i = 0; i < n; i++)
	{
		// f1
		y1k = y1i + AM4(epow_func, xi, y1i, y2i, y3i);

		// f2
		y2k = y2i + AM4(sin_func, xi, y1i, y2i, y3i);

		// f3
		y3k = y3i + AM4(sqrt_func, xi, y1i, y2i, y3i);

		plot_x.push_back(xi);
		plot_y1.push_back(y1i);
		plot_y2.push_back(y2i);
		plot_y3.push_back(y3i);

		if (i % 100 == 0)
		cout << setw(10) << xi << setw(10) << y1i << setw(10) << y2i << setw(10) << y3i << setw(10) << y1k << setw(10) << y2k << setw(10) <<  y3k << setw(10) << endl;
		xi += h;
		y1i = y1k;
		y2i = y2k;
		y3i = y3k;
	}
	// Displaying result
	cout << "\nValue of y1, y2, y3 at x = " << xk << " is " << y1k << " , " << y2k << " , " << y3k;
	
	DrawPlot(plot_x, plot_y1, plot_y2, plot_y3);
	
	return 0;
}
