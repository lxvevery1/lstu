#include <iostream>
#include <math.h>
using namespace std;

int main()
{
int n;
double a;
cin >> a >> n;
double s=(1/a);
while (n)
{
double tmp = 1.0;
for(int x = 1; x <= n; x++)
tmp /= (a + x);
s += tmp;
n--;
}
cout << s;
return 0;
}