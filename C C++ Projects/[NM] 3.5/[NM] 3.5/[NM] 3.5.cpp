// Метод прямых итераций
#include<iostream>
#include<iomanip>
#include<stdio.h>

#define SIZE 5

using namespace std;

int main()
{
	float /*a[SIZE][SIZE] = {{0.369080808,	1.436031013, -0.728668525,	0.990262713, -1.066533038},
					    	{9.321890071, -1.513583362, -3.530025844, -5.518609715,	1.735434769,},
							{0.53279339, -2.264422783, -4.01783643, -5.59560245, -3.516869824, },
							{1.624855009,	1.624346269, -2.438991881,	2.43852384,	2.741387029,},
							{-7.857573106, -1.199934881, -0.823975906,	0.389003073, -6.276184856} },*/ x[SIZE], x_new[SIZE];
	float temp, lambda_new, lambda_old, error;
	int i, j, n, step = 1;

	float a[SIZE][SIZE] = { {4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354},
	{1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 },
	{					-14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377},
	{					3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008},
	{				-0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128}
	};
	cout << setprecision(4) << fixed;

	n = SIZE;

	error = 0.0001;



	for (i = 0; i < n; i++)
	{
		x[i] = 1;
	}

	lambda_old = 1;

up:
	for (i = 0; i < n; i++)
	{
		temp = 0.0;
		for (j = 0; j < n; j++)
		{
			temp += a[i][j] * x[j];
		}
		x_new[i] = temp;
	}

	for (i = 0; i < n; i++)
	{
		x[i] = x_new[i];
	}

	// Finding largest value from x
	lambda_new = abs(x[1]);
	for (i = 0; i < n; i++)
	{
		if (abs(x[i]) > lambda_new)
		{
			lambda_new = abs(x[i]);
		}
	}

	// Normalization
	for (i = 0; i < n; i++)
	{
		x[i] /= lambda_new;
	}

	// Display
	cout << "\nEigen Value = " << lambda_new;
	cout << "\tEigen Vector: [";
	for (i = 0; i < n; i++)
	{
		cout << x[i] << "\t";
	}
	cout << "]";

	if (abs(lambda_new - lambda_old) >= error)
	{
		lambda_old = lambda_new;
		step++;
		goto up;
	}
	cout << "\nTotal iterations: " << step;
	return(0);
}