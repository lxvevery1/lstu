#include <iostream>
#include <cmath>
#include <pbPlots.cpp>
#include <supportLib.cpp>
#include <iomanip>
using namespace std;

double LagrangeBasis(double x, const vector<double>& nodes, int i)
{
    double result = 1;
    for (int j = 0; j < nodes.size(); j++)
    {
        if (j != i)
        {
            result *= (x - nodes[j]) / (nodes[i] - nodes[j]);
        }
    }
    return result;
}

double LagrangeInterpolation(double x, const vector<double>& nodes, const vector<double>& values)
{
    double result = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        result += values[i] * LagrangeBasis(x, nodes, i);
    }
    return result;
}

void plot(vector<double> x, vector<double> y, vector<double> nodes, vector<double> values) {

    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &x;
    series1->ys = &y;
    series1->lineType = toVector(L"solid");
    series1->pointType = toVector(L"circles");
    series1->linearInterpolation = true;
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
    settings->title = toVector(L"Lagrange's polynom");
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

int main()
{
    cout << setprecision(9);
    //Mine
    vector<double> nodes = { -0.9, -1, 0.083, 0.472, 1.347, 2.117, 2.947, 4, 4.1 };
    vector<double> values = { 2.9, 3, -2.132, -2.013, -1.613, -0.842, 2.973, -1, -1.1 };

    vector<double> example_x = { -1.1, -1, 4, 4.1 };
    vector<double> example_y = { 2.9, 3, -1, -0.9 };

    //From example
    //vector<double> nodes = { 0.351, 0.867, 3.315, 5.013, 6.432 };
    //vector<double> values = { -0.572, -2.015, -3.342, -5.752, -6.911 };

    // output the Lagrange basis polynomials
    cout << "Lagrange basis polynomials:\n";
    for (int i = 0; i < nodes.size(); i++)
    {
        cout << "L_" << i << "(x) = ";
        for (int j = 0; j < nodes.size(); j++)
        {
            if (j != i)
            {
                cout << "(x - " << nodes[j] << ") / (" << nodes[i] << " - " << nodes[j] << ")";
                if (j < nodes.size() - 1 && j != i - 1)
                {
                    cout << " * ";
                }
            }
        }
        cout << endl;
    }
    // -1; 3    -    4; -1
    // interpolate the values at some points
    double x;
    vector<double> x_vector;
    vector<double> y_vector;
    for (x = -1; x < 4.1; x += 0.1)
    {
        double y = LagrangeInterpolation(x, nodes, values);
        cout << setw(3) << x << setw(13) << y << endl;
        x_vector.push_back(x);
        y_vector.push_back(y);
    }

    cout << "Denominators of the Lagrange basis polynomials:\n";
    for (int i = 0; i < nodes.size(); i++)
    {
        double denominator = 1;
        for (int j = 0; j < nodes.size(); j++)
        {
            if (j != i)
            {
                denominator *= (nodes[i] - nodes[j]);
            }
        }
        cout << "L_" << i << " = " << 1.0 / denominator << endl;
    }

    plot(x_vector, y_vector, nodes, values);

    return 0;
}