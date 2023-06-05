#include <iostream>
#define n 4
using namespace std;
int main()
{
#pragma region Init
    long double a[4][4], b[4], x[4], accuracyCheck[4];
    // Swap rows 2 and 1 =>
    a[0][0] = 8.03;   a[0][1] = -3.33;    a[0][2] = -0.12;   b[0] = -0.17;
    a[1][0] = -0.92;  a[1][1] = 10.71;    a[1][2] = -0.22;   b[1] = 0.44;
    a[2][0] = 1.02;   a[2][1] = 0.5;      a[2][2] = 8.24;    b[2] = -0.69;

    a[0][0] = 9;
    a[0][1] = -3;
    a[0][2] = -12;
    a[0][3] = 9;
    b[0] = -84;

    a[1][0] = -3;
    a[1][1] = 26;
    a[1][2] = 24;
    a[1][3] = 7;
    b[1] = -162;

    a[2][0] = -12;
    a[2][1] = 24;
    a[2][2] = 57;
    a[2][3] = 16;
    b[2] = -275;

    a[3][0] = 9;
    a[3][1] = 7;
    a[3][2] = 16;
    a[3][3] = 45;
    b[3] = -476;

    float epsilon = .001;
    for (int i = 0; i < n; i++) {
        x[i] = b[i] / a[i][i];
    }
#pragma endregion
#pragma region Gauss-Seidel method
    int iter = 0;
    do {
        for (int i = 0; i < n; i++) {
            accuracyCheck[i] = x[i];
            x[i] = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) x[i] -= (a[i][j] * x[j]);
            }
            x[i] /= a[i][i];
        }
        iter++;
    } while ((abs(x[0] - accuracyCheck[0]) > epsilon || abs(x[1] - accuracyCheck[1]) > epsilon || abs(x[2] - accuracyCheck[2]) > epsilon));
#pragma endregion

    for (int i = 0; i < n; i++)
        cout << x[i] << " ";

    return 0;
}