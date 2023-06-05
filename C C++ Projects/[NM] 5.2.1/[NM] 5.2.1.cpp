#include <iostream>
#include <vector>
#include <pbPlots.cpp>
#include <supportLib.cpp>
#include <iomanip>
using namespace std;

vector<vector<double>> divided_differences_table(const vector<double>& nodes, const vector<double>& values) {
    int n = nodes.size();
    vector<vector<double>> f(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        f[i][0] = values[i];
    }
    for (int j = 1; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            f[i][j] = (f[i][j - 1] - f[i - 1][j - 1]) / (nodes[i] - nodes[i - j]);
        }
    }
    return f;
}

double newton_interpolation_polynomial(const vector<double>& nodes, const vector<double>& values, double x) {
    vector<vector<double>> f = divided_differences_table(nodes, values);
    double p = f[0][0];
    double prod = 1.0;
    int n = nodes.size();
    for (int i = 1; i < n; ++i) {
        prod *= (x - nodes[i - 1]);
        p += prod * f[i][i];
    }
    return p;
}

void plot(vector<double> x, vector<double> y, vector<double> nodes, vector<double> values) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x;
    series1->ys = &y;
    series1->lineType = toVector(L"solid");
    series1->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &nodes;
    series2->ys = &values;
    series2->lineType = toVector(L"solid");
    series2->pointType = toVector(L"circles");
    series2->linearInterpolation = false;
    series2->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 480;
    settings->title = toVector(L"Newton's polynom");
    settings->xLabel = toVector(L"X axis");
    settings->yLabel = toVector(L"Y axis");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);

    DrawScatterPlotFromSettings(imageReference, settings, NULL);

    vector<double>* pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    cout << "\nPlot generated\n";
    DeleteImage(imageReference->image);
}

int main() {
    cout << setprecision(9);
    //MINE
    vector<double> nodes = { -0.9, -1, 0.083, 0.472, 1.347, 2.117, 2.947, 4, 4.1 };
    vector<double> values = { 2.9, 3, -2.132, -2.013, -1.613, -0.842, 2.973, -1, -1.1 };

    //From example
    //vector<double> nodes = { 0.351, 0.867, 3.315, 5.013, 6.432 };
    //vector<double> values = { -0.572, -2.015, -3.342, -5.752, -6.911 };

    vector<double> x_vector;
    vector<double> y_vector;

    // Plot Newton interpolation polynomial
    for (double x = -1; x < 4.1; x += 0.1) {
        double y = newton_interpolation_polynomial(nodes, values, x);
        cout << setw(3) << x << setw(13) << y << endl;
        x_vector.push_back(x);
        y_vector.push_back(y);
    }

    // Print divided differences table
    vector<vector<double>> f = divided_differences_table(nodes, values);
    int n = nodes.size();
    cout << "Divided differences table:\n";
    for (int i = 0; i < n; ++i) {
        cout << nodes[i] << " ";
        for (int j = 0; j <= i; ++j) {
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }

    plot(x_vector, y_vector, nodes, values);

    return 0;
}
