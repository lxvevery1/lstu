#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    int n;
    double a;
    cin >> a;
    cin >> n;
    double s=(1.0/a);
    while (n)
    {
        double den = 1;
        for (int x = 0; x <= n; x++)
        den /= (a+x);
        s += den;
        n--;
    }
    cout << s;
    return 0;
}