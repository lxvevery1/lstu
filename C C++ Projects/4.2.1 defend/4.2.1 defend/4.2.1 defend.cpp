#include <iostream>
#include <cmath>
#include <iomanip>
#include <pbPlots.cpp>
#include <supportLib.cpp>

#define eps 1e-6

using namespace std;

void displayMatr2D(double matr[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << "\n";
    }
}

#pragma region Functions
double f1(double x1, double x2) {
    return x2 - 1.5 + cos(x1);
}
double f2(double x1, double x2) {
    return 2 * x1 - sin(x2 - 0.5) - 1;
}
double FplotF1(double x1) {
    return asin(1.2 * x1 + 1) - 0.5 * x1;
}
double FplotF2(double x1) {
    return sqrt(1 - pow(x1, 2));
}
#pragma endregion

#pragma region For_Newtons
double df1_dx1(double x1) {
    return -sin(x1);
}
double df1_dx2() {
    return 1;
}
double df2_dx1(double x1) {
    return 2.0;
}
double df2_dx2(double x2) {
    return -cos(x2-0.5);
}
#pragma endregion

#pragma region Default_Newton

void newton_default(double x1, double x2)
{
    double _f1, _f2, J[2][2], detJ, invJ[2][2], deltaX1, deltaX2, norm;
    int tick = 0;

    do {
        _f1 = f1(x1, x2);
        _f2 = f2(x1, x2);

        J[0][0] = df1_dx1(x1);
        J[0][1] = df1_dx2();
        J[1][0] = df2_dx1(x1);
        J[1][1] = df2_dx2(x2);

        detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];

        invJ[0][0] = J[1][1] / detJ;
        invJ[0][1] = -J[0][1] / detJ;
        invJ[1][0] = -J[1][0] / detJ;
        invJ[1][1] = J[0][0] / detJ;

        deltaX1 = invJ[0][0] * (-_f1) + invJ[0][1] * (-_f2);
        deltaX2 = invJ[1][0] * (-_f1) + invJ[1][1] * (-_f2);

        x1 += deltaX1;
        x2 += deltaX2;

        norm = fabs(deltaX1 + deltaX2);

        tick++;
    } while (norm > eps && tick < 100);

    cout << "\tDefault Newton's method";

    cout << "\nx1 = " << x1 << "\nx2 = " << x2 << "\n";
    cout << "Number of ticks: " << tick << "\n";
}

#pragma endregion

#pragma region Two_step_newton
void Two_step_newton(double x1, double x2)
{
    int tick = 0;
    double dx1, dx2;
    double J[2][2];
    do {
        double f1_val = f1(x1, x2);
        double f2_val = f2(x1, x2);
        J[0][0] = df1_dx1(x1);
        J[0][1] = df1_dx2();
        J[1][0] = df2_dx1(x1);
        J[1][1] = df2_dx2(x2);
        double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];

        dx1 = (-f1_val * J[1][1] + f2_val * J[0][1]) / detJ;
        dx2 = (f1_val * J[1][0] - f2_val * J[0][0]) / detJ;

        x1 += dx1;
        x2 += dx2;

        tick++;
    } while (fabs(dx1) > eps && fabs(dx2) > eps);

    cout << "\tTwo-step newton method\n";
    cout << "x1 = " << x1 << "\n";
    cout << "x2 = " << x2 << "\n";
    cout << "Number of ticks: " << tick << "\n";
}
#pragma endregion

#pragma region Seidel

void seidel_method(double x1, double x2)
{
    double x1_prev, x2_prev;
    double diff;
    double _f1, _f2;
    int iter = 0;
    do {
        x1_prev = x1;
        x2_prev = x2;

        // Вычисляем новое значение x1
        x1 = acos(1.5 - x2);

        // Вычисляем новое значение x2
        x2 = asin(2* x1 - 1) + 0.5;

        
        iter++;
    } while (x1 > eps || x2 > eps);

    cout << "\tSeidel method \n";
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "Number if ticks: " << iter << endl;
}

#pragma endregion

#pragma region Gradient_Descent

// Функция для вычисления значения Ф(x1, x2)
double Phi(double x1, double x2) {
    return pow(f1(x1, x2), 2) + pow(f2(x1, x2), 2);
}

// Функции для вычисления производных Ф(x1, x2) по x1 и x2
double dPhi_dx1(double x1, double x2, double h) {
    return (Phi(x1 + h, x2) - Phi(x1, x2)) / h;
}

double dPhi_dx2(double x1, double x2, double h) {
    return (Phi(x1, x2 + h) - Phi(x1, x2)) / h;
}

// Функция градиентного спуска
void gradient_descent(double x1, double x2, double step_size) {
    int i = 0, max_iterations = 10000;
    double dx1, dx2, temp_x1, temp_x2;
    double h = 0.0001; // шаг для вычисления производных

    while (i < max_iterations) {
        dx1 = dPhi_dx1(x1, x2, h);
        dx2 = dPhi_dx2(x1, x2, h);

        temp_x1 = x1 - step_size * dx1;
        temp_x2 = x2 - step_size * dx2;

        if (fabs(Phi(temp_x1, temp_x2) - Phi(x1, x2)) < eps) {
            break;
        }

        x1 = temp_x1;
        x2 = temp_x2;

        i++;
    }

    cout << "\tGradient descent method\n";
    cout << "x1 = " << x1 << "\n";
    cout << "x2 = " << x2 << "\n";
    cout << "Number of ticks: " << i << "\n";
}

#pragma endregion

int main() {
    double x1 = 0;
    double x2 = 0;
    cout << setprecision(8) << fixed;
    newton_default(x1, x2);
    cout << "\n\n";
    Two_step_newton(x1, x2);
    cout << "\n\n";
    seidel_method(x1, x2);
    cout << "\n\n";
    gradient_descent(0.0, 1.0, 0.03);
    cout << "\n\n";

    return 0;
}