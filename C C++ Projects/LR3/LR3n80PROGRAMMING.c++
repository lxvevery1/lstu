#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double fact(int n)
{
    return n == 0 ? 1.0 : n * fact(n - 1);
}
double sum(double x, int k = 13) 
{
    double acc = 0.0;
    for (int n = 1, m = 0; n <= k; n += 2, ++m) 
    {
    acc += pow(-1.0, m) * pow(x, n) / fact(n);
    }
        return acc;
}

int main() 
{
    cout << "x: ";
    double x;
    cin >> x;
    cout << "sum: " << sum(x) << '\n';
    return 0;
}