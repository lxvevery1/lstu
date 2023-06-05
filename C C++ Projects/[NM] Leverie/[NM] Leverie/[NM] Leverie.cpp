#include <iostream>
using namespace std;
#define N 3
int main() {
	float A[N][N], S[N], A1[N][N], A2[N][N], A3[N][N], P[N];
	A[0][0] = 5;
	A[0][1] = 6;
	A[0][2] = 3;
	A[1][0] = -1;
	A[1][1] = 0;
	A[1][2] = 1;
	A[2][0] = 1;
	A[2][1] = 2;
	A[2][2] = -1;

	
	// Считаем Ak
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A2[i][j] = A[i][j] * A[i][j];
			A3[i][j] = A2[i][j] * A2[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << A2[i][j] << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << A3[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	//Считаем S
	for (int i = 0; i < N; i++) {
		S[i] = 0;
		for (int j = 0; j < N; j++) {
			if (j == i)
				S[i] += A[i][j] + A2[i][j] + A3[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		cout << S[i] << " ";
	}
	cout << "\n";

	cout << "P: \n";
	// Считаем P
	for (int i = 0; i < N; i++) {
		P[i] = 0;
		P[0] = S[0];
		if (i != 0)
		P[i] = (S[i] - (P[0] * S[i-1]) - (P[1]*S[i-2])) * (1 / (i+1));
		cout << P[i] << " ";
	}
	return 0;
}