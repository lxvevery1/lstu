#include<iostream>
#include<cmath>
#include<iomanip>
#include<C:\Users\lxve_every1\Desktop\plots\pbPlots.hpp>
#include<C:\Users\lxve_every1\Desktop\plots\supportLib.hpp>
using namespace std;
// Defining ordinary system of differential equationes to be solved
#define f1(x, y) (1 / cosh(x + y))
#define f2(x, y) (sinh(pow(x,2) - y))
constexpr auto h = 0.01;

double func1(double xi, double yi) {
	double k1, k2, k3, k4, k5, k;

	// for dy1_dx
	k1 = h * (f1(xi, yi));
	k2 = h * (f1(xi + h / 3, yi + k1 / 3));
	k3 = h * (f1(xi + h / 3, yi + k1 / 6 + k2 / 6));
	k4 = h * (f1(xi + h / 2, yi + k1 / 8 + 3 * k3 / 8));
	k5 = h * (f1(xi + h, yi + k1 / 2 - (3 * k3 / 2) + 2 * k4));
	return (k1 + 4 * k4 + k5) / 6;
}

double func2(double xi, double yi) {
	double k1, k2, k3, k4, k5, k;

	// for dy1_dx
	k1 = h * (f2(xi, yi));
	k2 = h * (f2(xi + h / 3, yi + k1 / 3));
	k3 = h * (f2(xi + h / 3, yi + k1 / 6 + k2 / 6));
	k4 = h * (f2(xi + h / 2, yi + k1 / 8 + 3 * k3 / 8));
	k5 = h * (f2(xi + h, yi + k1 / 2 - (3 * k3 / 2) + 2 * k4));
	return (k1 + 4 * k4 + k5) / 6;
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
	cout << setw(15) <<"xi" << setw(15) << "y1i" << setw(15) << "y2i" << setw(15) << "y1k" << setw(15) << "y2k\n";
	cout << "---------------------------------------------------------------------------\n";
	for (i = 0; i < n; i++)
	{
		// for dy1_dx
		ky1 = func1(xi, y2i);
		y2k = y2i + ky1;

		// for dy2_dx
		ky2 = func2(xi, y1i);
		y1k = y1i + ky2;

		//if (i % 20 == 0)
			cout << setw(15) << xi << setw(15) << y2i << setw(15) << y1i << setw(15) << y2k << setw(15) << y1k << endl;
		xi += h;
		y1i = y1k;
		y2i = y2k;
	}
	// Displaying result
	cout << "\nValue of y1, y2 at x = " << xk << " is " << y2k << " , " << y1k;

	return 0;
}
