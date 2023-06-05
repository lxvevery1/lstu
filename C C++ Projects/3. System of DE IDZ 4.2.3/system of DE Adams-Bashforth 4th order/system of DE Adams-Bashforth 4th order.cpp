#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
#define exp 2.7182818284
// Defining ordinary system of differential equationes to be solved
#define f1(xi, y1i, y2i, y3i) cos(y1i * y2i * y3i)
#define f2(xi, y1i, y2i, y3i) pow(exp, (xi*y1i*y3i))
#define f3(xi, y1i, y2i, y3i) sin(y1i*y2i*y3i)

#define f1(xi, yi, y2i, y3i) -y2i + sin(xi * y3i)
#define f2(xi, yi, y2i, y3i) pow(y1i, 2)
#define f3(xi, yi, y2i, y3i) -y3i - y1i

double cos_func(double xi, double y1i, double y2i, double y3i, double h)
{
	double k1, k2, k3, k4, k;
	k1 = f1(xi, y1i, y2i, y3i);
	k2 = 5 * f1(xi, y1i, y2i, y3i);
	k3 = 19 * f1(xi, y1i, y2i, y3i);
	k4 = 9 * f1(xi, y1i, y2i, y3i);
	k = (h / 24) * (k4 + k3 - k2 + k1);
	return k;
}
double pow_func(double xi, double y1i, double y2i, double y3i, double h)
{
	double k1, k2, k3, k4, k;
	k1 = f2(xi, y1i, y2i, y3i);
	k2 = 5 * f2(xi, y1i, y2i, y3i);
	k3 = 19 * f2(xi, y1i, y2i, y3i);
	k4 = 9 * f2(xi, y1i, y2i, y3i);
	k = (h / 24) * (k4 + k3 - k2 + k1);
	return k;
}
double sin_func(double xi, double y1i, double y2i, double y3i, double h)
{
	double k1, k2, k3, k4, k;
	k1 = f3(xi, y1i, y2i, y3i);
	k2 = 5 * f3(xi, y1i, y2i, y3i);
	k3 = 19 * f3(xi, y1i, y2i, y3i);
	k4 = 9 * f3(xi, y1i, y2i, y3i);
	k = (h / 24) * (k4 + k3 - k2 + k1);
	return k;
}

int main()
{
	double xi, y1i, y2i, y3i, xk, h, y1k, y2k, y3k, eps,
		ky1, ky2, ky3;

	int i, n;

	y1i = -2;
	y2i = 1;
	y3i = 3;

	xi = 1;
	xk = 5;

	y1i = 1;
	y2i = 0;
	y3i = 1;

	xi = 0;
	xk = 2;

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
		ky1 = cos_func(xi, y1i, y2i, y3i, h);
		y1k = y1i + ky1;

		// f2
		ky2 = pow_func(xi, y1i, y2i, y3i, h);
		y2k = y2i + ky2;

		// f3
		ky3 = sin_func(xi, y1i, y2i, y3i, h);
		y3k = y3i + ky3;

		//if (i % 20 == 0)
		cout << setw(10) << xi << setw(10) << y1i << setw(10) << y2i << setw(10) << y3i << setw(10) << y1k << setw(10) << y2k << setw(10) << y3k << setw(10) << endl;
		xi += h;
		y1i = y1k;
		y2i = y2k;
		y3i = y3k;
	}
	// Displaying result
	cout << "\nValue of y1, y2, y3 at x = " << xk << " is " << y1k << " , " << y2k << " , " << y3k;

	return 0;
}
