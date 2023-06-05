#include <iostream>
using namespace std;
#define n1 4
int i, n, j;
double z, matrix[n1][n1], B[n1], eps[n1], sol[n1], et[n1], res[n1], temp[n1];

int main()
{
#pragma region Init
    matrix[0][0] = 1;
    matrix[0][1] = 9;
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = -1;
    matrix[1][1] = -2;
    matrix[1][2] = -8;
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = -9;
    matrix[2][2] = 0;
    matrix[2][3] = 3;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = -8;
    matrix[3][3] = 1;

    B[0] = 33;
    B[1] = -76;
    B[2] = -42;
    B[3] = -69;


#pragma endregion
#pragma Solution
#pragma Thomas
    n = n1 - 1;
    eps[0] = -matrix[0][1] / matrix[0][0];
    et[0] = B[0] / matrix[0][0];

    for (i = 1; i < n; i++)
    {
        z = matrix[i][i] + matrix[i][i - 1] * eps[i - 1];
        eps[i] = -matrix[i][i + 1] / z;
        et[i] = (B[i] - matrix[i][i - 1] * et[i - 1]) / z;
    }

    sol[n] = (B[n] - matrix[n][n - 1] * et[n - 1]) / (matrix[n][n] + matrix[n][n - 1] * eps[n - 1]);

    for (i = n - 1; i >= 0; i--)
        sol[i] = eps[i] * sol[i + 1] + et[i];

    
#pragma endregion
#pragma endregion 

#pragma region Residual
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n1; j++)  {
                temp[i] += matrix[i][j] * sol[j];
            }
    }

    for (i = 0; i < n1; i++)
    {
        res[i] = 0;
        res[i] += temp[i]-B[i];
            
    }
   

#pragma endregion
    cout << "Solution: \n";
    for (i = 0; i < n1; i++)
        cout << sol[i] << " ";

    cout << "\nResidual: \n";

    for (i = 0; i < n1; i++) {
        cout << res[i] << " ";
    }
    return 0;
}