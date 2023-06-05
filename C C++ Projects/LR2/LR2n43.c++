//43. Даны три действительных числа. Возвести в квадрат те из них, значения которых неотрицательны.
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<locale.h>
using namespace std;

int main(){
    float x, y, z;
    setlocale(LC_ALL, "");

    
    cout << "Введите x: ";
    cin >>x;
    cout << "Введите y: ";
    cin >>y;
    cout << "Введите z: ";
    cin >>z;

    if (x>=0)
    cout << endl <<"x = " << x*x <<endl;
    if (y>=0)
    cout << endl <<"y = " << y*y <<endl;
    if (z>=0)
    cout << endl <<"z = " << z*z <<endl;
}
