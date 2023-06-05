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
    return sin(0.5 * x1 + x2) - 1.2  * x1 - 1;
}
double f2(double x1, double x2) {
    return pow(x1, 2) + pow(x2, 2) - 1;
}
double FplotF1(double x1) {
    return asin(1.2 * x1 + 1) - 0.5 * x1;
}
double FplotF2(double x1) {
    return sqrt(1-pow(x1, 2));
}
#pragma endregion

#pragma region For_Newtons
double df1_dx1(double x1, double x2) {
    return 0.5 * cos(0.5 * x1 + x2) - 1.2;
}
double df1_dx2(double x1, double x2) {
    return cos(0.5 * x1 + x2);
}
double df2_dx1(double x1) {
    return 2 * x1;
}
double df2_dx2(double x2) {
    return 2  *x2;
}
#pragma endregion

/* Example
double f1(double x1, double x2) {
    return sin(x1 + 1.5) - x2 + 2.9;
}
double f2(double x1, double x2) {
    return cos(x2 - 2) + x1;
}
double df1_dx1(double x1, double x2) {
    return cos(x1 + 1.5);
}
double df1_dx2(double x1, double x2) {
    return -1;
}
double df2_dx1(double x1) {
    return 1;
}
double df2_dx2(double x2) {
    return -sin(x2 - 2);
}

// For Seidel method
double g1(double x1, double x2) {
    return -cos(x2-2);
}
double g2(double x1, double x2) {
    return sin(x1+1.5)+2.9;
}
*/


#pragma region Default_Newton

void jacobian(double x1, double x2, double& j11, double& j12, double& j21, double& j22)
{
    j11 = df1_dx1(x1, x2);
    j12 = df1_dx2(x1, x2);
    j21 = df2_dx1(x1);
    j22 = df2_dx2(x2);
}
void inverse(double j11, double j12, double j21, double j22, double& inv_j11, double& inv_j12, double& inv_j21, double& inv_j22)
{
    double det = j11 * j22 - j12 * j21;

    inv_j11 = j22 / det;
    inv_j12 = -j12 / det;
    inv_j21 = -j21 / det;
    inv_j22 = j11 / det;
}

void newton_default(double x1, double x2)
{
    double _f1, _f2, J[2][2], detJ, invJ[2][2], deltaX1, deltaX2, norm;
    int tick = 0;

    do {
        _f1 = f1(x1, x2);
        _f2 = f2(x1, x2);

        J[0][0] = df1_dx1(x1, x2);
        J[0][1] = df1_dx2(x1, x2);
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
    } while (norm > eps);

    cout << "\tDefault Newton's method";
    //cout << "\nJacobean matrix: \n";
    //displayMatr2D(J);
    //cout << "\nInversed Jacobean matrix: \n";
    //displayMatr2D(invJ);
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
        J[0][0] = df1_dx1(x1, x2);
        J[0][1] = df1_dx2(x1, x2);
        J[1][0] = df2_dx1(x1);
        J[1][1] = df2_dx2(x2);
        double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];

        dx1 = (-f1_val * J[1][1] + f2_val * J[0][1]) / detJ;
        dx2 = (f1_val * J[1][0] - f2_val * J[0][0]) / detJ;

        x1 += dx1;
        x2 += dx2;

        tick++;
    }
    while (fabs(dx1) > eps && fabs(dx2) > eps);

    cout << "\tTwo-step newton method\n";
    cout << "x1 = " << x1 << "\n";
    cout << "x2 = " << x2 << "\n";
    cout << "Number of ticks: " << tick << "\n";
}
#pragma endregion

#pragma region Seidel
// For Seidel method
double g1(double x1, double x2) {
    return (sin(0.5 * x1 + x2) - 1) / (1.2); // pow(sin(1.2 * x1 + 1), -1) - 0.5 * x1 // 2 * (asin(1.2 * x1 + 1) - x2) // (sin(0.5 * x1 + x2) - 1) / 1.2
}
double g2(double x1, double x2) {
    return sqrt(1 - pow(x1, 2)); // sqrt(1 - pow(x1, 2)) // sqrt(1 - pow(x2, 2))
}

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
        x1 = (sin(0.5 * x1_prev + x2) - 1) / 1.2;

        // Вычисляем новое значение x2
        x2 = sqrt(1 - pow(x1, 2));

        /*
        double f1(double x1, double x2) {
            return sin(0.5 * x1 + x2) - 1.2 * x1 - 1;
        }
        double f2(double x1, double x2) {
            return pow(x1, 2) + pow(x2, 2) - 1;
        }
        */

        _f1 = sin(0.5 * x1 + x2) - 1.2 * x1 - 1;
        _f2 = pow(x1, 2) + pow(x2, 2) - 1;

        iter++;
    } while (_f1 > eps || _f2 > eps);

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
    double x1 = 2.0;
    double x2 = 2.0;
    cout << setprecision(8) << fixed;
    newton_default(x1, x2);
    cout << "\n\n";
    Two_step_newton(x1, x2);
    cout << "\n\n";
    seidel_method(x1, x2);
    cout << "\n\n";
    gradient_descent(0.0, 1.0, 0.03);
    cout << "\n\n";



#pragma region Plot
    double a = -1;
    double b = 1;
    vector<double> f1_array;
    vector<double> f2_array;
    vector<double> x_array;
    double temp = a;
    while (temp <= b) {
        x_array.push_back(temp);
        f1_array.push_back(FplotF1(temp));
        f2_array.push_back(FplotF2(temp));
        temp += 0.1;
    }

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x_array;
    series1->ys = &f1_array;
    series1->lineType = toVector(L"solid");
    series1->color = CreateRGBColor(0, 0, 1);


    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &x_array;
    series2->ys = &f2_array;
    series2->lineType = toVector(L"solid");
    series2->color = CreateRGBColor(0, 1, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"asin(1.2 * x1 + 1) - 0.5 * x1 (B) && sqrt(1 - pow(x1, 2)) (G)");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);

#pragma endregion

    return 0;
}