#include <iostream>
using namespace std;
int MatrMult() {
	const int N = 3;
	size_t i, j, k;
	double A[N][N];
	double B[N][N];
	double C[N][N];
	cout << "Matrix A:\n";

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = 1 + rand() % 9;
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}

	cout << "Matrix B:\n";
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			B[i][j] = 1 + rand() % 9;
			cout << B[i][j] << ' ';
		}
		cout << endl;
	}

	cout << "Matrix C=AB:\n";
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i][j] = 0;
			for (k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
			cout << C[i][j] << " ";
		}
		cout << endl;
	}

	return C[i][j];
}

int main() {
	size_t i, j, N = 3;

    cout << MatrMult();
	return 0;
}