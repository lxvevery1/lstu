#include<iostream>
#define n 3
using namespace std;
int main()
{
#pragma region Init
    int i, j, k, flag = 0, count = 0;
    double a[n][n + 1];
    double x[n] = { 0, 0, 0 };
    double tmp = 0;
    double eps, y;


    a[0][0] = -0.92;
    a[0][1] = 10.71;
    a[0][2] = -0.22;
    a[0][3] = 0.44;

    a[1][0] = 8.03;
    a[1][1] = -3.33;
    a[1][2] = -0.12;
    a[1][3] = -0.17;

    a[2][0] = 1.02;
    a[2][1] = 0.5;
    a[2][2] = 8.24;
    a[2][3] = -0.69;

    ///////////////////////////

    a[0][0] = 1;
    a[0][1] = -2;
    a[0][2] = -4;
    a[0][3] = 1;

    a[1][0] = -2;
    a[1][1] = 13;
    a[1][2] = -7;
    a[1][3] = 46;

    a[2][0] = -4;
    a[2][1] = -7;
    a[2][2] = 50;
    a[2][3] = -102;

    eps = .001;
    for (i = 0; i < n; i++)
        for (k = i + 1; k < n; k++)
            if (abs(a[i][i]) < abs(a[k][i]))
                for (j = 0; j <= n; j++)
                {
                    double temp = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = temp;
                }
#pragma endregion

#pragma region Solution Yakobi

#pragma region Gauss
    for (i = 0; i < n; i++) // Прямой ход
    {
        tmp = a[i][i];
        for (j = n; j >= i; j--)
            a[i][j] /= tmp; //Приведение матрицы к трапециевидному типу
        for (j = i + 1; j < n; j++)
        {
            tmp = a[j][i];
            for (k = n; k >= i; k--)
                a[j][k] -= tmp * a[i][k];
        }
    }
#pragma endregion

    do
    {
        for (i = 0; i < n; i++)
        {
            y = x[i];
            x[i] = a[i][n];
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    x[i] = x[i] - a[i][j] * x[j];

                cout << "Number of iteration: " << i << "\n";
                cout << x[i] << "\n";
            }
            x[i] = x[i] / a[i][i];
            cout << "Number of iteration: " << i << "\n";
            cout << x[i] << "\n";
            if (abs(x[i] - y) <= eps) {
                flag++;
                cout << "\nflag++\n";
            }
        }
        count++;
        cout << "\ncount++\n";
    } while (flag < n);
    for (i = 0; i < n; i++)
        cout << x[i] << " ";
#pragma endregion
    return 0;
}