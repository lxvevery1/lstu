#include <iostream>
# define N 4
typedef double matrix[N][N];
matrix l, u, a;
long double b[N], sol[N], v[N];
using namespace std;

void urow(int i)
{
    float s;
    int j, k;
    for (j = i; j < N; j++)
    {
        s = 0;
        for (k = 0; k < i; k++)
            s += u[k][j] * l[i][k];
        u[i][j] = a[i][j] - s;
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
            s += u[k][j] * l[i][k];
        l[i][j] = (a[i][j] - s) / u[j][j];
    }
}

void printmat(matrix x)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            cout << x[i][j] << " ";
        cout << endl;
    }
}

int main()
{
#pragma endregion

#pragma region Initialising
    int i, j, m;
    float s, residual = 0;
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
#pragma endregion 

#pragma region OutputOfOurMatrix
    cout << "Matrix: " << endl;
    for (int i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
#pragma endregion

#pragma region Solution
    //Forward move, приведение системы к трапециевидной
    int k;

#pragma region LU
 
    for (i = 0; i < N; i++)
        l[i][i] = 1.0;
    for (m = 0; m < N; m++)
    {
        urow(m);
        if (m < (N - 1))
            lcol(m);
    }
    cout << "L: \n";
    printmat(l);
    cout << "\n";
    cout << "U: \n";
    printmat(u);


    for (i = 0; i < N; i++)
    {
        s = 0;
        for (j = 0; j <= i - 1; j++)
            s += l[i][j] * v[j];
        v[j] = b[i] - s;
    }
    for (i = N - 1; i >= 0; i--)
    {
        s = 0;
        for (j = i + 1; j < N; j++)
            s += u[i][j] * sol[j];
        sol[i] = (v[i] - s) / u[i][i];
    }
    


#pragma endregion

#pragma region Residual
    {
        double* res; double* temp;
        res = new double[N];
        temp = new double[N];

        for (i = 0; i < N; i++) {
            temp[i] = 0;
            for (j = 0; j < N; j++) {
                temp[i] += sol[j] * a[i][j];
            }
        }

        for (i = 0; i < N; i++) 
        {
            res[i] = abs(temp[i] - b[i]);
            residual += res[i];
        }

#pragma endregion
#pragma endregion
        //Output solution
        cout << "\nSolution: \n";
        for (i = 0; i < N; i++) {
            cout << sol[i] << " ";
        }
        cout << "\nResidual: \n";
        cout << residual;
    }

    return 0;
}