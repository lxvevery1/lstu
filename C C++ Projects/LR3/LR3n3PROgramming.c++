#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
 
int main()
{
    setlocale(LC_ALL, "");
    int height;
    cout << "¬ведите высоту равнобедренного треугольника: ";
    cin >> height;
 
    for (int i = 0; i < height; ++i)
        cout << setw(height + i) << string(i * 2 + 1, '*') << endl;
 
return 0;
}