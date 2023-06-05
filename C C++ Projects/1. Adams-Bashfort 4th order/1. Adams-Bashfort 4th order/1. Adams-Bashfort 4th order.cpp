// Adams-Bashfort 4th order
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
		k1 = 9 * f(xi, yi);
		k2 = 37 * f(xi, yi);
		k3 = 59 * f(xi, yi);
		k4 = 55 * f(xi, yi);
		yk = yi + (h / 24) * (k4 - k3 + k2 - k1);


		if (i % 100 == 0)
			cout << xi << "\t" << yi << "\t" << yk << endl;
		xi += h;
		yi = yk;
	}
	// Displaying result
	cout << "\nValue of y at x = " << xk << " is " << yk;

	return 0;
}
