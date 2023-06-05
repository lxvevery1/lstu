#include <iostream>
#include <cmath>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>

using namespace std;

double a = 13, b = 4, k = 3, c = 5, d = 8, m = 100;

double function(double x) {
	return pow(log(x), a / b) * sin(k * x);
}

double Lagrange(double x, vector<double> x_values, vector<double> y_values, int n) {
	double L = 0;
	for (int i = 0; i <= n; i++) {
		double l = 1;
		for (int j = 0; j <= n; j++) {
			if (i != j) {
				l *= (x - x_values[j]) / (x_values[i] - x_values[j]);
			}
		}
		L += y_values[i] * l;
	}
	return L;
}

double NewtonCotes4(double a, double b) {
	double h = (b - a) / 4;
	double x0 = a;
	double x1 = x0 + h;
	double x2 = x1 + h;
	double x3 = x2 + h;
	double x4 = b;
	return (h / 90) * (7 * function(x0) + 32 * function(x1) + 12 * function(x2) + 32 * function(x3) + 7 * function(x4));
}

double NewtonCotes5(double a, double b) {
	double h = (b - a) / 5;
	double x0 = a;
	double x1 = x0 + h;
	double x2 = x1 + h;
	double x3 = x2 + h;
	double x4 = x3 + h;
	double x5 = b;
	return (h / 288) * (19 * function(x0) + 75 * function(x1) + 50 * function(x2) + 50 * function(x3) + 75 * function(x4) + 19 * function(x5));
}

void table(vector<double> res, string method) {
	cout << "Method: " << method << endl;
	cout << "n \t\t Result" << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << i + 1 << " \t\t " << res[i] << endl;
	}
	cout << endl;
}

void plot(vector<double> x, vector<double> leftRes, vector<double> rightRes, vector<double> middleRes, vector<double> trapRes, vector<double> simpRes) {

	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries* seriesLeftRes = GetDefaultScatterPlotSeriesSettings();
	seriesLeftRes->xs = &x;
	seriesLeftRes->ys = &leftRes;
	seriesLeftRes->lineType = toVector(L"solid");
	seriesLeftRes->pointType = toVector(L"circles");
	seriesLeftRes->linearInterpolation = true;
	seriesLeftRes->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSeries* seriesRightRes = GetDefaultScatterPlotSeriesSettings();
	seriesRightRes->xs = &x;
	seriesRightRes->ys = &rightRes;
	seriesRightRes->lineType = toVector(L"solid");
	seriesRightRes->pointType = toVector(L"circles");
	seriesRightRes->linearInterpolation = true;
	seriesRightRes->color = CreateRGBColor(0, 1, 0);

	ScatterPlotSeries* seriesMiddleRes = GetDefaultScatterPlotSeriesSettings();
	seriesMiddleRes->xs = &x;
	seriesMiddleRes->ys = &middleRes;
	seriesMiddleRes->lineType = toVector(L"solid");
	seriesMiddleRes->pointType = toVector(L"circles");
	seriesMiddleRes->linearInterpolation = true;
	seriesMiddleRes->color = CreateRGBColor(0, 0, 0);

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

	vector<ScatterPlotSeries*> series({ seriesLeftRes, seriesRightRes, seriesMiddleRes, seriesTrapRes, seriesSimpRes });

	settings->scatterPlotSeries->push_back(seriesLeftRes);
	settings->scatterPlotSeries->push_back(seriesRightRes);
	settings->scatterPlotSeries->push_back(seriesMiddleRes);
	settings->scatterPlotSeries->push_back(seriesTrapRes);
	settings->scatterPlotSeries->push_back(seriesSimpRes);

	DrawScatterPlotFromSettings(imageReference, settings, NULL);

	vector<double>* pngData = ConvertToPNG(imageReference->image);
	WriteToFile(pngData, "plot.png");
	cout << "\nPlot generated\n";
	DeleteImage(imageReference->image);
}

int main() {
	vector<double> x, y, x_l, y_l;

	vector<double> NC4, NC5, L4, L5;

	double h = (d - c) / m;

	for (double i = c; i <= d; i += h) {
		x.push_back(i);
		y.push_back(function(i));
	}

	double step = (d - c) / (m);

	double x_point = c;
	while (x_point <= d) {
		x_l.push_back(x_point);
		y_l.push_back(function(x_point));

		x_point += step;
	}

	for (int i = 0; i < x_l.size(); i++) {
		L4.push_back(Lagrange(x_l[i], x, y, 3));
		L5.push_back(Lagrange(x_l[i], x, y, 4));


		NC4.push_back(NewtonCotes4(x_l[i], y[i]));
		NC5.push_back(NewtonCotes5(x_l[i], y[i]));
	}

	table(NC4, "NC4");
	table(NC5, "NC5");
	table(L4, "L4");
	table(L5, "L5");

	plot(x, L4, L5, NC4, NC5, NC4);

	return 0;
}