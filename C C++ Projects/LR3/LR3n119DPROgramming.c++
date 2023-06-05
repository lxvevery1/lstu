#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double s = 1.0/6.0, t = s, e;
    cout << "e = ";
    cin >> e;

    for(int i = 1; fabs(t) > e; ++i)
    {
        t *= -i/(i+3.0);
        s += t;
    }
    cout << s << endl;
    return 0;
}