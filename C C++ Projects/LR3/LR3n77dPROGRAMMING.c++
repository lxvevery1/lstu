#include <iostream>
#include <math.h>
using namespace std;


int main()
{
    setlocale(LC_ALL, "");

    int n;
    double s = sqrt(2);

    cout << "Введите число корней n: ";
    cin >> n;

    for(int i=1;i<n;i++)
     s=sqrt(s+2);
    cout <<"Ответ: " << s;
return 0;
}
