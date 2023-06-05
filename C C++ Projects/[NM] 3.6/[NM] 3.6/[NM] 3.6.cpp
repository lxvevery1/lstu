#include <iostream>
#include <cmath>

using namespace std;

const int N = 5; // matrix dimension
const double eps = 0.0001; // accuracy

void print_matrix(double A[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
}

void inverse_iteration(double A[N][N], double& lambda)
{
    double x[N], x_new[N], y[N], y_new[N];
    double norm = 0, lambda_new, delta = 1;
    int iter = 0;

    // initial guess
    for (int i = 0; i < N; i++)
    {
        x[i] = 1.0;
    }

    while (delta > eps)
    {
        iter++;
        // solve linear system
        for (int i = 0; i < N; i++)
        {
            y[i] = 0.0;
            for (int j = 0; j < N; j++)
            {
                y[i] += A[i][j] * x[j];
            }
        }

        // find the norm of y
        norm = 0.0;
        for (int i = 0; i < N; i++)
        {
            norm += y[i] * y[i];
        }
        norm = sqrt(norm);

        // normalize y
        for (int i = 0; i < N; i++)
        {
            y[i] /= norm;
        }

        // calculate new eigenvalue
        lambda_new = 0.0;
        for (int i = 0; i < N; i++)
        {
            lambda_new += x[i] * y[i];
        }
        lambda_new += 3;

        // check for convergence
        delta = fabs(lambda_new - lambda);
        lambda = lambda_new;

        // update x
        for (int i = 0; i < N; i++)
        {
            x[i] = y[i];
        }
    }

    cout << "Number of iterations: " << iter << endl;
}

int main()
{
    /*
    double A[N][N] =   { {0.37,	1.44, -0.7,	0.99, -1.1 },
                        { 9.32, -1.5, -3.5, -5.5, 1.74 },
                        { 0.53, -2.3, -4,   -5.6, -3.5 },
                        { 1.62,	1.62, -2.4,	2.44, 2.74 },
                        { -7.9, -1.2, -0.8,	0.39, -6.3 } };
    */
    double A[N][N] = { {4.935279658,	11.22995589,	7.490992356,	9.252651783,	3.132774354},
    {               1.98774287, -4.155200862,	1.78913695, -0.601474896, -4.903054181 },
    {					-14.85166852, -14.99269286, -17.98117655, -6.935448025,	3.670202377},
    {					3.110179479, 1.867629727, 1.115230495, -3.164764118, 3.172509008},
    {				-0.635350372, -2.132774354, -1.226824258, 1.39387817, -2.634138128}
    };
    double lambda = 0.0;

    cout << "Matrix A:\n";
    print_matrix(A);

    inverse_iteration(A, lambda);

    cout << "The minimum eigenvalue is: " << lambda<< endl;

    return 0;
}