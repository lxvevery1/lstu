#include <iostream>
using namespace std;

double** Table1(int n, int m, double** matrix) {

    matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];

    matrix[0][0] = -0.92;
    matrix[0][1] = 10.71;
    matrix[0][2] = -0.22;
    matrix[0][3] = 0.44;

    matrix[1][0] = 8.03;
    matrix[1][1] = -3.33;
    matrix[1][2] = -0.12;
    matrix[1][3] = -0.17;

    matrix[2][0] = 1.02;
    matrix[2][1] = 0.5;
    matrix[2][2] = 8.24;
    matrix[2][3] = -0.69;

    return matrix;
}
double** Table2(int n, int m, double** matrix) {

    matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];

    matrix[0][0] = 9;
    matrix[0][1] = -6;
    matrix[0][2] = -3;
    matrix[0][3] = 6;
    matrix[0][4] = -60;

    matrix[1][0] = -6;
    matrix[1][1] = 13;
    matrix[1][2] = 5;
    matrix[1][3] = 11;
    matrix[1][4] = -173;

    matrix[2][0] = -3;
    matrix[2][1] = 5;
    matrix[2][2] = 27;
    matrix[2][3] = 13;
    matrix[2][4] = -306;

    matrix[3][0] = 6;
    matrix[3][1] = 11;
    matrix[3][2] = 13;
    matrix[3][3] = 49;
    matrix[3][4] = -625;

    return matrix;
}
double** Table3(int n, int m, double** matrix) {

    matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];

    matrix[0][0] = 1;
    matrix[0][1] = 9;
    matrix[0][2] = 0;
    matrix[0][3] = 0;
    matrix[0][4] = 33;

    matrix[1][0] = -1;
    matrix[1][1] = -2;
    matrix[1][2] = -8;
    matrix[1][3] = 0;
    matrix[1][4] = -76;

    matrix[2][0] = 0;
    matrix[2][1] = -9;
    matrix[2][2] = 0;
    matrix[2][3] = 3;
    matrix[2][4] = -42;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = -8;
    matrix[3][3] = 1;
    matrix[3][4] = -69;

    return matrix;
}

double** Table4(int n, int m, double** matrix) {

    matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];

    matrix[0][0] = 9;
    matrix[0][1] = -3;
    matrix[0][2] = -12;
    matrix[0][3] = 9;
    matrix[0][4] = -84;

    matrix[1][0] = -3;
    matrix[1][1] = 26;
    matrix[1][2] = 24;
    matrix[1][3] = 7;
    matrix[1][4] = -162;

    matrix[2][0] = -12;
    matrix[2][1] = 24;
    matrix[2][2] = 57;
    matrix[2][3] = 16;
    matrix[2][4] = -275;

    matrix[3][0] = 9;
    matrix[3][1] = 7;
    matrix[3][2] = 16;
    matrix[3][3] = 45;
    matrix[3][4] = -476;

    return matrix;
}


int main()
{
    float residual = 0;
    int i = 0, j = 0, n = 0, m = 0, choice = 0;
    bool task1_1 = false, task1_2 = false, task1_3 = false, task1_4 = false;

#pragma region taskChoose
    cout << "Choose a task to deal with: ";
    cout << "\n1. Task 1.1\n2. Task 1.2\n3. Task 1.3\n4. Task 1.4\n";
    cin >> choice;

    switch (choice) {
    case 1: task1_1 = true;
    case 2: task1_2 = true;
    case 3: task1_3 = true;
    case 4: task1_4 = true;
    default: "Wrong input!\n";
        break;
    }
#pragma endregion

#pragma region matrixCreation
    if (task1_1) {
        n = 3;
        m = 3 + 1;
    }
    else if (task1_2 || task1_3 || task1_4) {
        n = 4;
        m = 4 + 1;
    }
#pragma endregion

#pragma region Initialising
    double** matrix = new double* [n];
    for (i = 0; i < n; i++)
        matrix[i] = new double[m];

    if (task1_1) {
        matrix = Table1(n, m, matrix);
    }
    else if (task1_2) {
        matrix = Table2(n, m, matrix);
    }
    else if (task1_3) {
        matrix = Table3(n, m, matrix);
    }
    else if (task1_4) {
        matrix = Table4(n, m, matrix);
    }

#pragma endregion 

#pragma region OutputOfOurMatrix
    cout << "Matrix: " << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
#pragma endregion

#pragma region Solution
    float tmp, * sol;
    sol = new float[m];
    int k;

#pragma region Gauss
    for (i = 0; i < n; i++) // Прямой ход
    {
        tmp = matrix[i][i];
        for (j = n; j >= i; j--)
            matrix[i][j] /= tmp; //Приведение матрицы к трапециевидному типу
        for (j = i + 1; j < n; j++) 
        {
            tmp = matrix[j][i];
            for (k = n; k >= i; k--)
                matrix[j][k] -= tmp * matrix[i][k];
        }
    }
    //Обратный ход
    sol[n - 1] = matrix[n - 1][n];
    for (i = n - 2; i >= 0; i--)
    {
        sol[i] = matrix[i][n];
        for (j = i + 1; j < n; j++) sol[i] -= matrix[i][j] * sol[j];
    }
    
#pragma endregion

#pragma region Residual
    {
        float* res; float* temp;
        res = new float[m];
        temp = new float[m];
        
        for (i = 0; i < n; i++) {
            temp[i] = 0;
            for (j = 0; j < n; j++) {
                temp[i] += sol[j] * matrix[i][j];
            }
        }

        for (i = 0; i < n; i++) {
            res[i] = abs(matrix[i][m - 1] - temp[i]);
            residual += res[i];
        }

#pragma endregion
#pragma endregion
        //Output solution
        cout << "\nSolution: \n";
        for (i = 0; i < n; i++)
            cout << sol[i] << " ";
        cout << "\nResidual: \n";
        cout << residual;
    }

    delete[] matrix;
    return 0;
}