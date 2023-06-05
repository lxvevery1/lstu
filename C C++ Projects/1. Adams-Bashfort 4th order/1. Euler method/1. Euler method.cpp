// Runge-Kutta method 4th order
#include<iostream>
#include<iomanip>
using namespace std;
// Defining ordinary differential equation to be solved
#define f(x,y) (cos(x*y))


int main()
{
	double xi, yi, xk, h, yk, k1, k2, k3, k4, k, eps, r;
	int i, n;
	xi = 1;
	yi = 3;
	xk = 4;
	eps = 0.001;

	n = (xk - xi) / eps;

	//step size
	h = eps;
	
	// Algorithm
	cout << setw(15) <<" xi " << setw(15) << " yi " << "\n";
	cout << "--------------------------------------\n";
	for (i = 0; i < n; i++)
	{
		k = h * (f(xi, yi));

		yk = yi + k;

		
		if (i % 100 == 0)
			cout << xi << setw(15) << yi << setw(15) << yk << endl;
		xi = xi + h;
		yi = yk;
	}

	// Displaying result
	cout << "\nValue of y at x = " << xk << " is " << yk;
	
	return 0;
}

