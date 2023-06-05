#include<iostream>
#include<cmath>
#include<iomanip>
#include<C:\Users\lxve_every1\Desktop\plots2\pbPlots.hpp>
#include<C:\Users\lxve_every1\Desktop\plots2\supportLib.hpp>
using namespace std;
// Defining ordinary system of differential equationes to be solved
#define dy1_dx(xi, y2i) 1 / cosh(xi + y1i)
#define dy2_dx(xi, y1i) sinh(pow(xi, 2) - y2i)
constexpr auto h = 0.01;

double cosh_func(double x, double y) 
{
	return h * 1 / cosh(x + y);
}

double sinh_func(double x, double y) 
{
	return h * sinh(x*x - y);
}

int main()
{
	double xi, y1i, y2i, xk, h, y1k, y2k, eps, ky1, ky2;
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
		ky1 = cosh_func(xi, y2i);
		y2k = y2i + ky1;

		ky2 = sinh_func(xi, y1i);
		y1k = y1i + ky2;

		plot_x.push_back(xi);
		plot_y1.push_back(y1i);
		plot_y2.push_back(y2i);

		//if (i % 20 == 0)
		cout << setw(15) << xi << setw(15) << y1i << setw(15) << y2i << setw(15) << y1k << setw(15) << y2k << endl;
		xi += h;
		y1i = y1k;
		y2i = y2k;
	}
	// Displaying result
	cout << "\nValue of y1, y2 at x = " << xk << " is " << y1k << " , " << y2k;
	//DrawPlot(plot_x, plot_y1, plot_y2);
	return 0;
}
