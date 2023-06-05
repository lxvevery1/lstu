#include<iostream>
#include<iomanip>
#include<pbPlots.cpp>
#include<supportLib.cpp>

using namespace std;
# define M_PI 3.14159265358979323846
constexpr auto h = 0.01;
// Defining ordinary system of differential equationes to be solved

double func(double xi, double yi, double y1i, double y2i)
{
	return cbrt(pow(xi, 4) - 2 * xi + 1) -
		(tan(pow(xi, 2) - 1) * y2i + pow(xi, 2) * sin(pow(xi, 2) - 1) * y1i +
			sin((xi + 2) / 2) * yi);
}

double Eul(double (*f) (double, double, double, double), double xi,
	double yi, double y1i, double y2i)
{
	return h * f(xi, yi, y1i, y2i);
}

double RK4(double (*f) (double, double, double, double), double xi,
	double yi, double y1i, double y2i)
{
	double k1 = h * f(xi, yi, y1i, y2i);
	double k2 = h * f(xi + h / 2, yi + k1 / 2, y1i
		+ k1 / 2, y2i + k1 / 2);
	double k3 = h * f(xi + h / 2, y1i + k2 / 2,
		y1i + k2 / 2, y2i + k2 / 2);
	double k4 = h * f(xi + h, yi + k3, y1i + k3,
		y2i + k3);
	return (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

double RK5(double (*f) (double, double, double, double), double xi,
	double yi, double y1i, double y2i)
{
	double k1, k2, k3, k4, k5, k;
	k1 = h * (f(xi, yi, y1i, y2i));
	k2 = h * (f(xi + h / 3, yi + k1 / 3, y1i + k1
		/ 3, y2i + k1 / 3));
	k3 = h * (f(xi + h / 3, yi + k1 / 6, y1i + k1
		/ 6 + k2 / 6, y2i + k1 / 6 + k2 / 6));
	k4 = h * (f(xi + h / 2, yi + k1 / 8 * k3 / 8,
		y1i + k1 / 8 + 3 * k3 / 8, y2i + k1 / 8 + 3 * k3 / 8));
	k5 = h * (f(xi + h, yi + k1 / 2 - (3 * k3 / 2) + 2
		* k4, y1i + k1 / 2 - (3 * k3 / 2) + 2 * k4, y2i + k1 / 2 - (3 * k3 / 2)
		+ 2 * k4));
	k = (k1 + 4 * k4 + k5) / 6;
	return k;
}

double AB4(double (*f) (double, double, double, double), double xi,
	double yi, double y1i, double y2i)
{
	double k1, k2, k3, k4, k;
	k1 = f(xi, yi, y1i, y2i);
	k2 = 5 * f(xi, yi, y1i, y2i);
	k3 = 19 * f(xi, yi, y1i, y2i);
	k4 = 9 * f(xi, yi, y1i, y2i);
	k = (h / 24) * (k4 + k3 - k2 + k1);
	return k;
}

double AM4(double (*f) (double, double, double, double), double xi,
	double yi, double y1i, double y2i)
{
	double k1, k2, k3, k4, k;
	k1 = 9 * f(xi, yi, y1i, y2i);
	k2 = 37 * f(xi, yi, y1i, y2i);
	k3 = 59 * f(xi, yi, y1i, y2i);
	k4 = 55 * f(xi, yi, y1i, y2i);
	k = (h / 24) * (k4 - k3 + k2 - k1);
	return k;
}

void DrawPlot(vector<double> x, vector<double> y) {
	RGBABitmapImageReference* imageRef =
		CreateRGBABitmapImageReference();

	ScatterPlotSeries* series1 =
		GetDefaultScatterPlotSeriesSettings();
	series1->xs = &x;
	series1->ys = &y;
	series1->linearInterpolation = false;
	series1->lineType = toVector(L"solid");
	series1->color = CreateRGBColor(0, 0, 1);

	ScatterPlotSettings* settings =
		GetDefaultScatterPlotSettings();
	settings->width = 800;
	settings->height = 480;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"");
	settings->xLabel = toVector(L"x");
	settings->yLabel = toVector(L"y");
	settings->scatterPlotSeries->push_back(series1);


	DrawScatterPlotFromSettings(imageRef,
		settings, NULL);

	vector<double>* pngData =
		ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "plot.png");
	DeleteImage(imageRef->image);
}

int main()
{
	double xi, yi, y1i, y2i, y3i{}, xk, h, yk,
		eps;
	vector<double> plot_x, plot_y;
	int i, n;

	xi = -1;
	xk = M_PI / 2;

	yi = -1;
	y1i = 0;
	y2i = -0.5;

	eps = 0.01;
	n = (xk - xi) / eps;
	// Calculating step size (h)
	h = eps;

	// Algorithm
	cout << setw(20) << "xi" << setw(20) <<
		"yi\n";
	cout << "--------------------------------------\n";
		for (i = 0; i < n; i++)
		{
			yk = yi + Eul(func, xi, yi, y1i, y2i);

			plot_x.push_back(xi);
			plot_y.push_back(yi);

			if (i % 100 == 0)
				cout << setw(20) << xi << setw(20) <<
				yi << setw(20) << endl;
			xi += h;
			yi = yk;
		}
	// Displaying result
	cout << "\nValue of y at x = " << xk << " is " << yk;

		DrawPlot(plot_x, plot_y);

	return 0;
}