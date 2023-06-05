#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    int height;
    cout << "Введите высоту прямоугольного треугольника: ";
    cin >> height;

    for(int i=1; i<=height; i++) {
    for(int j=0; j<i; j++)
     cout << "*";
       cout << endl;
    }
return 0;
}