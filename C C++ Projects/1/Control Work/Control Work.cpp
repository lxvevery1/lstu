#include <iostream>
#include <iomanip>
#include "matrix.h"
#include "polynom.h"

using namespace std;

int main()
{
	cout << setprecision(5) << fixed;

	int n = 5;
	matrix A;

	double m[5][5] = { {4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354},
	{1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 },
	{					-14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377},
	{					3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008},
	{				-0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128}
	};


	matrix B(m);
	cout << "Matrix : \n";
	cout << B;
	A = B;

	matrix S(n);
	matrix F = A.toFrobenius(S);
	cout << "Frobenius matrix: \n";
	cout << F;
	polynom P(n + 1);
	polynom Q(2);
	P.setPolynom(F.getPolynom());

	cout << "Characteristic polynomial: \n";
	cout << P;
	cout << "E: " << endl;

	return 0;
}