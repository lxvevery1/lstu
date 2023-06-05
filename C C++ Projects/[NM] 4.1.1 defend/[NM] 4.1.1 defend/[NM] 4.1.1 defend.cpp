#include <iostream>
#include <cmath>
#include <iomanip>
#include <pbPlots.cpp>
#include <supportLib.cpp>
using namespace std;

double f(double x) {
    return pow(x, 0.5) - 1 / x * log(x) - 2.5;
}
double df(double x) {
    return (0.5 * pow(x, -0.5) + 1 / pow(x,  2) * log(x) - 1 / pow(x,2));
}
double phi_test(double x) {
    return x - 0.1 * (pow(x, 0.5) - 1 / x * log(x) - 2.5); //(log(x) + 2.5 * x) / (pow(x, 0.5))
}

// Для графического представления функций разделим нашу f на f1 и f2
double f1(double x) {
    return pow(x, 0.5);
}
double f2(double x) {
    return - 1 / x * log(x) - 2.5;
}

double dichotomy(double a, double b, double eps) {
    int ticks = 0;
    while (b - a >= eps) {
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        ticks++;
    }
    cout << "Number of dichotomy method ticks: " << ticks;
    return (a + b) / 2;
}

double newton(double x, double eps) {
    double x_next = x - f(x) / df(x);
    int ticks = 0;
    while (abs(x_next - x) >= eps) {
        x = x_next;
        x_next = x - f(x) / df(x);
        ticks++;
    }
    cout << "\nNumber of Newton's method ticks: " << ticks;
    return x_next;
}

double phi(double x) {

    double temp = 0.1;
    vector<double> tut_maxs;
    double Q = df(0.1); // Инициализация максимального значения
    while (temp <= 1) {
        double df_val = df(temp);
        tut_maxs.push_back(df_val);
        if (fabs(df_val) > fabs(Q)) { // Если новое значение больше максимального !ПО МОДУЛЮ, обновляем его
            Q = df_val;
        }
        temp += 0.001;
    }
    int k = round((Q / 2));
    return x - f(x) / k;
}

double simple_iteration(double x0, double eps) {
    double x1 = phi(x0);
    int ticks = 0;
    while (fabs(x1 - x0) > eps && ticks < 10000) {
        x0 = x1;
        x1 = phi(x0);
        ticks++;
    }
    cout << "\nNumber of simple iteration method ticks: " << ticks;
    return x1;
}

double steffensen(double x, double eps) {
    double x0, x1 = x, fpx;
    int ticks = 0;
    do {
        x0 = x1;
        fpx = (f(x0 + f(x0)) - f(x0));
        x1 = x0 - (pow(f(x0), 2)) / fpx;

        ticks++;
    } while (abs(f(x1)) > eps);
    cout << "\nNumber of ticks: " << ticks;
    return x0;
}



int main() {
    cout << setprecision(7) << fixed;
    double eps = 1e-6;
    double a = 0.1;
    double b = 1;
    
    double dihRoot = dichotomy(a, b, eps);
    cout << "\nDichotomy root = " << dihRoot << "\n";

    double newtRoot = newton((b - a) / 2, eps);
    cout << "\nNewton root = " << newtRoot << "\n";

    double simpleIterRoot = simple_iteration(0.1, eps); // where 1st argument is x0
    cout << "\nSimple iteration root = " << simpleIterRoot << "\n";

    double steffensenRoot = steffensen((b - a) / 2, eps); // where 1st argument is x0
    cout << "\nSteffensen's method root = " << steffensenRoot << "\n";

    return 0;
}