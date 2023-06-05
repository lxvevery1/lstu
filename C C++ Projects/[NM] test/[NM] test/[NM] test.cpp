#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
#define n 4
int main()
{
    int i, j, k, m;
    float A[n][n], L[n][n], T[n][n];
    float g[n], r[n], v[n], y[n], pk, sum;

    m = n;
    //открываем поток для работы с файлами
    ifstream f("2.txt", ios::in);
    //считываем из потока m
    //f >> m;
    //cout << " m = "<< m << "\n" ;
    //считываем из потока матрицу и вектор g
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            f >> A[i][j];
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    for (i = 0; i < m; i++)
    {
        f >> g[i];
        cout << g[i] << " ";
    }
    f.close(); // закрываем поток, т.к. все что нам надо мы считали

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++)
            L[i][j] = 0;

    //Нахождение матрицы L и T соответственно
    L[0][0] = sqrt(A[0][0]);
    for (j = 1; j < m; j++)
        L[j][0] = A[j][0] / L[0][0];

    for (i = 1; i < m; i++)
    {
        sum = 0;
        for (k = 0; k < i; k++)
            sum = sum + L[i][k] * L[i][k]; //можно pow(L[i][j],2)
        pk = A[i][i] - sum;
        L[i][i] = sqrt(pk);

        for (j = i + 1; j < m; j++)
        {
            sum = 0;
            for (k = 0; k < i; k++)
                sum = sum + L[j][k] * L[i][k];
            pk = A[j][i] - sum;
            L[j][i] = pk / L[i][i];
        }
    }

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++)
            T[i][j] = L[j][i];

    //Решение L*v=g
    v[0] = g[0] / L[0][0];
    for (i = 1; i < m; i++)
    {
        sum = 0;
        for (k = 0; k < i; k++)
            sum = sum + L[i][k] * v[k];
        pk = g[i] - sum;
        v[i] = pk / L[i][i];
    }

    //Решение T*y=v
    y[m - 1] = v[m - 1] / T[m - 1][m - 1];
    for (i = m - 2; i >= 0; i--)
    {
        sum = 0;
        for (k = i + 1; k < m; k++)
            sum = sum + T[i][k] * y[k];
        pk = v[i] - sum;
        y[i] = pk / T[i][i];
    }

    // Нахождение вектора невязки r
    for (i = 0; i < m; i++)
    {
        r[i] = 0;
        for (j = 0; j < m; j++)
            r[i] = r[i] + A[i][j] * y[j];
        r[i] = r[i] - g[i];
    }

    cout << "\n";
    for (i = 0; i < m; i++)
        cout << y[i] << " ";
    cout << "\n";
    for (i = 0; i < m; i++)
        cout << r[i] << " ";

    return 0;
}