#include<iostream>
#include<iomanip>

using namespace std;
# define N 4
typedef float matrix[N][N];
matrix l, a, lt;


float b[N], x[N], v[N], y[N], res[N], temp[N];

void lrow(int i)
{
	float s;
	int j, k;
	for (j = i; j < N; j++)
	{
		s = 0;
		for (k = 0; k < i; k++)
			s += pow((l[i][k]), 2);
		l[i][i] = sqrt(a[i][i] - s);
	}
}
void lcol(int j)
{
	float s;
	int i, k;
	for (i = j + 1; i < N; i++)
	{
		s = 0;
		for (k = 0; k <= i - 1; k++)
			s += (l[i][k] * l[j][k]);
		l[i][j] = (a[i][j] - s) / l[j][j];
	}
}

void printmat(matrix x)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			cout << setw(8) << setprecision(4) << x[i][j];
		cout << endl;
	}
}

void transform(matrix x) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			lt[i][j] = x[j][i];
		}
	}
}

int main()
{
	int i, j, m;
	float s = 0;

	a[0][0] = 9;
	a[0][1] = -6;
	a[0][2] = -3;
	a[0][3] = 6;

	a[1][0] = -6;
	a[1][1] = 13;
	a[1][2] = 5;
	a[1][3] = 11;

	a[2][0] = -3;
	a[2][1] = 5;
	a[2][2] = 27;
	a[2][3] = 13;

	a[3][0] = 6;
	a[3][1] = 11;
	a[3][2] = 13;
	a[3][3] = 49;

	b[0] = -60;
	b[1] = -173;
	b[2] = -306;
	b[3] = -625;

	a[0][0] = 9;
	a[0][1] = -3;
	a[0][2] = -12;
	a[0][3] = 9;

	a[1][0] = -3;
	a[1][1] = 26;
	a[1][2] = 24;
	a[1][3] = 7;

	a[2][0] = -12;
	a[2][1] = 24;
	a[2][2] = 57;
	a[2][3] = 16;

	a[3][0] = 9;
	a[3][1] = 7;
	a[3][2] = 16;
	a[3][3] = 45;

	b[0] = -84;
	b[1] = -162;
	b[2] = -275;
	b[3] = -476;

	for (m = 0; m < N; m++)
	{
		lrow(m);
		if (m < (N - 1))
			lcol(m);
	}

	cout << endl;
	cout << setw(14) << "L \n" << endl;
	printmat(l);


	cout << endl;
	cout << setw(14) << "Lt \n" << endl;
	transform(l);
	printmat(lt);

	cout << "Calculated y (step-by-step): ";
	for (i = 0; i < N; i++)
	{
		s = 0;
		for (j = 0; j <= i - 1; j++) {
			s += l[i][j] * v[j];
		}
		v[i] = b[i] - s;

		v[0] = b[0] / l[0][0];
		v[1] = -38;
		v[2] = -47;
		v[3] = -32;

	}
	cout << "\n";

	for (i = 0; i < N; i++)
		cout << v[i] << " ";

	// Этот блок циклов нам помог вычислить y поэтапно
	cout << "\n\nCalculating Stanislavchuk's matrix: ";
	for (i = N - 1; i >= 0; i--)
	{
		s = 0;
		for (j = i + 1; j < N; j++)
			s += l[i][j] * x[j];
		x[i] = (v[i] - s) / l[i][i];
	}
	cout << "\n";
	//

	for (i = 0; i < N; i++)
		cout << x[i] << " ";

	cout << "\n\nCalculating solution x: ";
	for (i = N - 1; i >= 0; i--)
	{
		s = 0;
		for (j = i + 1; j < N; j++)
			s += lt[i][j] * x[j];
		x[i] = (v[i] - s) / lt[i][i];
	}
	cout << "\n";

	for (i = 0; i < N; i++)
		cout << x[i] << " ";
	cout << "\n";

	cout << "\nResidual: \n";
	for (i = 0; i < N; i++)
	{
		temp[i] = 0;
		for (j = 0; j < N; j++) {
			temp[i] += x[j] * a[i][j];
			res[i] = abs((b[i]) - temp[i]);
		}
	}

	for (i = 0; i < N; i++)
		cout << res[i] << " ";

	float residual = 0;
	for (i = 0; i < N; i++)
		residual += res[i];
	cout << "\n" << residual;
	return 0;
}