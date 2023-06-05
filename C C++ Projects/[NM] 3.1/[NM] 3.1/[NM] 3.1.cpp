#include <iostream>
#include <iomanip>
#define n 5
using namespace std;

void matrPow(double An[n][n], double Ak[n][n], int t) {
	double temp[n][n];

	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = Ak[i][j];
		}
	}
	while (t > 1) {
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				An[i][j] = 0;
				for (int k = 0; k < n; k++)
					An[i][j] += temp[i][k] * Ak[k][j];
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				temp[i][j] = An[i][j];
			}
		}
		t--;
	}
}
void matr1DDisplay(double An[n]) {
	for (int i = 0; i < n; i++) {
			cout << An[i] << "\t";
		}
	cout << "\n";
}
void matr2DDisplay(double An[n][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(10) << An[i][j] ;
		}
		cout << "\n";
	}
}
double diagonalSum(double Sn, double An[n][n]) {
	for (int i = 0; i < n; i++){
			Sn += An[i][i];
		}
	return Sn;
}

int main()
{
	cout << setprecision(2) << fixed;
	double A2[n][n], A3[n][n], A4[n][n], A5[n][n],
		S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0,
		P1 = 0, P2 = 0, P3 = 0, P4 = 0, P5 = 0;

	/*double A1[n][n] = {{0.37,	1.44, -0.7,	0.99, -1.1},
							{ 9.32, -1.5, -3.5, -5.5, 1.74 },
							{ 0.53, -2.3, -4,   -5.6, -3.5 },
							{ 1.62,	1.62, -2.4,	2.44, 2.74 },
							{ -7.9, -1.2, -0.8,	0.39, -6.3 } };
	*/

	double A1[n][n] = { {4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354},
	{					1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 },
	{					-14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377},
	{					3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008},
	{					-0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128}
};
	
	
	// Calculating A
	matrPow(A2, A1, 2);
	matrPow(A3, A1, 3);
	matrPow(A4, A1, 4);
	matrPow(A5, A1, 5);
	
	// Displaying A
	cout << "A^1: \n";
	matr2DDisplay(A1);
	cout << "A^2: \n";
	matr2DDisplay(A2);
	cout << "A^3: \n";
	matr2DDisplay(A3);
	cout << "A^4: \n";
	matr2DDisplay(A4);
	cout << "A^5: \n";
	matr2DDisplay(A5);
	cout << "\n";
	//Calculatin Sn
	S1 = diagonalSum(S1, A1);
	S2 = diagonalSum(S2, A2);
	S3 = diagonalSum(S3, A3);
	S4 = diagonalSum(S4, A4);
	S5 = diagonalSum(S5, A5);
	
	// Displaying Sn
	cout << "S_1: "; cout << S1 << "\n";
	cout << "S_2: "; cout << S2 << "\n";
	cout << "S_3: "; cout << S3 << "\n";
	cout << "S_4: "; cout << S4 << "\n";
	cout << "S_5: "; cout << S5 << "\n\n";

	// Calculating P
	P1 = S1;
	P2 = (S2 - P1 * S1) * (0.5);
	P3 = (S3 - P1 * S2 - P2 * S1) * (0.333333333);
	P4 = (S4 - P1 * S3 - P2 * S2 - P3 * S1) * (0.25);
	P5 = (S5 - P1 * S4 - P2 * S3 - P3 * S2 - P4 * S1) * (0.2);

	//Displaying P
	cout << "P_1: " << P1 << "\n";
	cout << "P_2: " << P2 << "\n";
	cout << "P_3: " << P3 << "\n";
	cout << "P_4: " << P4 << "\n";
	cout << "P_5: " << P5 << "\n\n";

	// [WA] D(A) = ((-1)^5)*(x^5-(-8.99)*x^4-(29.31*x^3)-(249.26*x^2)-(-470.49*x)-(-660.32))
	
	// => x = {-8.00609, -7.02325, -0.973873, 3.01897, 3.99424)

	return 0;
}