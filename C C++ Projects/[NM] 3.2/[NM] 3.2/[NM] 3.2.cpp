﻿#include <iostream>
#include <iomanip>
#define n 5
using namespace std;

void matr2DDisplay(double An[n][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(10) << An[i][j];
		}
		cout << "\n";
	}
}

double diagonalSum(double Sn, double An[n][n]) {
	for (int i = 0; i < n; i++) {
		Sn += An[i][i];
	}
	return Sn;
}

void calcA(double B1[n][n], double B2[n][n], double P, double res[n][n]) {
	double unit[n][n], Brackets[n][n];

	for (int i = 0; i < n; i++) { // Calculating identity matrix
		for (int j = 0; j < n; j++) {
			unit[i][j] = 0;

			if (i == j)
				unit[i][j] = 1;
		}
	}

	// Brackets open
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Brackets[i][j] = B2[i][j] - (P * unit[i][j]);
		}
	}
	// Brackets close

	// Multiply
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = 0;
			for (int k = 0; k < n; k++)
				res[i][j] += B1[i][k] * Brackets[k][j];
		}
	}
}
void calcB(double Ak[n][n], double Pk, double E[n][n], double Bk[n][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Bk[i][j] = Ak[i][j] - Pk * E[i][j];
		}
	}
}

void calcAinv(double Bk[n][n], double Pn, double res[n][n]) {

	// Multiply
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = 0;
			res[i][j] = Bk[i][j] / Pn;
		}
	}
}
void calcEigVect(double B1[n][n], double B2[n][n], double B3[n][n], double B4[n][n], double x[n], double res[n][n], int k) {
	double unit[n][n];

	for (int i = 0; i < n; i++) { // Calculating identity matrix
		for (int j = 0; j < n; j++) {
			unit[i][j] = 0;

			if (i == j)
				unit[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = 0.0;
			res[i][j] = (pow(x[k], n - 1) * unit[i][j])
				+ (pow(x[k], n - 2) * B1[i][j])
				+ (pow(x[k], n - 3) * B2[i][j])
				+ (pow(x[k], n - 4) * B3[i][j])
				+ (pow(x[k], n - 5) * B4[i][j]);
		}
	}
	cout << "For x[" << k << "]: " << x[k] << "\n";
}

int main()
{
	cout << setprecision(2) << fixed;
	double A1[n][n], A2[n][n], A3[n][n], A4[n][n], A5[n][n], B1[n][n], B2[n][n], B3[n][n], B4[n][n], B5[n][n], Ainv[n][n], E[n][n], R1[n][n], R2[n][n], R3[n][n], R4[n][n], R5[n][n], temp1[n][n], temp2[n][n], temp3[n][n], temp4[n][n], temp5[n][n],
		Tr1 = 0, Tr2 = 0, Tr3 = 0, Tr4 = 0, Tr5 = 0,
		P1 = 0, P2 = 0, P3 = 0, P4 = 0, P5 = 0;

	/*double A[n][n] = {{0.369080808,	1.436031013, -0.728668525,	0.990262713, -1.066533038},
						{9.321890071, -1.513583362, -3.530025844, -5.518609715,	1.735434769,},
						{0.53279339, -2.264422783, -4.01783643, -5.59560245, -3.516869824, },
						{1.624855009,	1.624346269, -2.438991881,	2.43852384,	2.741387029,},
						{-7.857573106, -1.199934881, -0.823975906,	0.389003073, -6.276184856} };*/
						/*
						double A[n][n] = { {4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354},
						{				   1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 },
						{				   -14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377},
						{				   3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008},
						{				   -0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128}
						};
						*/
						
	double A[n][n] = {{ -68.45454545, -111.0909091, -104.8636364, -224.5454545, -169.2272727, },
	{-65.73150106, -121.9323467, -108.9038055, -234.3382664, -177.7262156 },
	{42.2832981,	70.9217759,	62.87315011,	145.3911205,	109.7928118 },
	{- 5.046511628, - 2.255813953, - 3.941860465, - 12.72093023, - 6.988372093, },
	{50.51585624,	81.20084567,	78.08245243,	167.9957717,	123.2346723, }};
						
	/*
	double A[n][n] = { { 3,5,7,2,3},
		{4,1,8,9,8 },
		{1, 5, 10, 6, 2},
		{6,8,8,4,3},
		{0,4,8,10,7 } };*/
	/*
						double A[n][n] = 
						{ { 5, 6, 3},
							{-1, 0, 1},
							{1, 2, -1} };
							
							*/
	// Displaying A

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A1[i][j] = A[i][j];
			R1[i][j] = 0.0;
			R2[i][j] = 0.0;
			R3[i][j] = 0.0;
			R4[i][j] = 0.0;
			R5[i][j] = 0.0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			E[i][j] = 0.0;
			E[i][i] = 1;
		}
	}

	//Calculatin Pn
	cout << "A1: \n"; matr2DDisplay(A1);
	P1 = diagonalSum(Tr1, A1);
	calcB(A1, P1, E, B1);
	cout << "B1: \n"; matr2DDisplay(B1);

	calcA(A1, A1, P1, A2);
	cout << "A2: \n"; matr2DDisplay(A2);
	P2 = 0.5 * diagonalSum(Tr2, A2);
	calcB(A2, P2, E, B2);
	cout << "B2: \n"; matr2DDisplay(B2);

	calcA(A1, A2, P2, A3);
	cout << "A3: \n"; matr2DDisplay(A3);
	P3 = (1 / 3.) * diagonalSum(Tr3, A3);
	calcB(A3, P3, E, B3);
	cout << "B3: \n"; matr2DDisplay(B3);
	
	calcA(A1, A3, P3, A4);
	cout << "A4: \n"; matr2DDisplay(A4);
	P4 = 0.25 * diagonalSum(Tr4, A4);
	calcB(A4, P4, E, B4);
	cout << "B4: \n"; matr2DDisplay(B4);

	calcA(A1, A4, P4, A5);
	cout << "A5: \n"; matr2DDisplay(A5);
	P5 = 0.2 * diagonalSum(Tr5, A5);
	calcB(A5, P5, E, B5);
	cout << "B5: \n"; matr2DDisplay(B5);
	

	//Displaying P
	cout << "\nP_1: " << P1 << "\n";
	cout << "P_2: " << P2 << "\n";
	cout << "P_3: " << P3 << "\n";
	cout << "P_4: " << P4 << "\n";
	cout << "P_5: " << P5 << "\n\n";

	/*
	// Calculating the inverse matrix A^(-1)
	calcAinv(A1, P2, P2, Ainv);

	cout << "Ainv: \n";
	matr2DDisplay(Ainv);

	cout << "PROOF: AA^(-1) = E\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			E[i][j] = 0;
			for (int k = 0; k < n; k++)
				E[i][j] += A1[i][k] * Ainv[k][j];
		}
	}
	*/
	
	//double x[5] = { -2.0, 2.0, 4.0 };
	//double x[5] = { -9.0, -8.0, -7.0, -2.0, 3.0 };
	
	//double x[5] = { -8.05768, -6.96634, -0.925153, 2.95372, 3.99545 };

	//double x[5] = { -9.0, -8.0, -7.0, -2.0, 3.0 };
	double x[5] = { -8.0, -6.0, -5.0, -3.0, 5.0 };



	calcEigVect(B1, B2, B3, B4, x, R1, 0);
	calcEigVect(B1, B2, B3, B4, x, R2, 1);
	calcEigVect(B1, B2, B3, B4, x, R3, 2);
	calcEigVect(B1, B2, B3, B4, x, R4, 3);
	calcEigVect(B1, B2, B3, B4, x, R5, 4);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp1[i][j] = 0;
			temp1[i][j] = R1[i][0] / R1[i][j];
			temp2[i][j] = R2[i][0] / R2[i][j];
			temp3[i][j] = R3[i][0] / R3[i][j];
			temp4[i][j] = R4[i][0] / R4[i][j];
			temp5[i][j] = R5[i][0] / R5[i][j];
		}
	}


	cout << "Eigen vector matrix R1:\n";
	matr2DDisplay(R1);
	cout << "Eigen vector matrix R2:\n";
	matr2DDisplay(R2);
	cout << "Eigen vector matrix R3:\n";
	matr2DDisplay(R3);
	cout << "Eigen vector matrix R4:\n";
	matr2DDisplay(R4);
	cout << "Eigen vector matrix R5:\n";
	matr2DDisplay(R5);


	cout << "matrix temp1:\n";
	matr2DDisplay(temp1);
	cout << "matrix temp2:\n";
	matr2DDisplay(temp2);
	cout << "matrix temp3:\n";
	matr2DDisplay(temp3);
	cout << "matrix temp4:\n";
	matr2DDisplay(temp4);
	cout << "matrix temp5:\n";
	matr2DDisplay(temp5);

	return 0;
}