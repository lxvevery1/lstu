//34. ���� �������������� ����� x, y, z. ��������:
//a) max(x,y,z)
//�) min(x,y,z)
#include<conio.h>
#include<stdio.h>
#include<iostream> 
using namespace std;

int main(){
    int x, y, z;
 
    cout << "Input x, y, z: ";
    cin >> x >> y >> z;
    if ((x>y)&&(x>z))
    cout << "a) Number " << x << " has maximum value\n";
    else if ((y>x)&&(y>z))
    cout << "a) Number " << y << " has maximum value\n";
    else if ((z>x)&&(z>y))
    cout << "a) Number " << z << " has maximum value\n";
    else if (x==y==z)
    cout << "a) Numbers are equals, there no maximum value\n";


    if ((x<y)&&(x<z))
    cout << "b) Number " << x << " has minimum value\n";
    else if ((y<x)&&(y<z))
    cout << "b) Number " << y << " has minimum value\n";
    else if ((z<x)&&(z<y))
    cout << "b) Number " << z << " has minimum value\n";
    else if (x==y==z)
    cout << "b) Numbers are equals, there no minimum value\n";
}   