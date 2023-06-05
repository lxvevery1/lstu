// Runge-Kutta method 5th order
#include<iostream>
using namespace std;
// Defining ordinary differential equation to be solved
#define f(x,y) (cos(x*y))


int main()
{
	double xi, yi, xk, h, yk, k1, k2, k3, k4, k5, k, eps;
	int i, n;
	xi = 1;
	yi = 3;
	xk = 4;
	eps = 0.001;

	n = (xk - xi) / eps;

	// Calculating step size (h)
	h = eps;

	// Algorithm
	cout << "xi\tyi\tyk\n";
	cout << "------------------\n";
	for (i = 0; i < n; i++)
	{
		k1 = h * (f(xi, yi));
		k2 = h * (f(xi + h / 3, yi + k1 / 3));
		k3 = h * (f(xi + h / 3, yi + k1 / 6 + k2 / 6));
		k4 = h * (f(xi + h / 2, yi + k1 / 8 + 3 * k3 / 8));
		k5 = h * (f(xi + h, yi + k1 / 2 - (3 * k3 / 2) + 2 * k4));
		k = (k1 + 4 * k4 + k5)/6;

		yk = yi + k;

		if (i % 100 == 0)
			cout << xi << "\t" << yi << "\t" << yk << endl;
		xi += h;
		yi = yk;
	}
	// Displaying result
	cout << "\nValue of y at x = " << xk << " is " << yk;

	return 0;
}
