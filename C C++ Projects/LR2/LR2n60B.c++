//60. ѕусть D Ц заштрихованна€ часть плоскости (рис. 1, аЧ3, е) и пусть u определ€етс€ по x и y следующим образом (запись (x, y) ? D означает, что точка с координатами x, y принадлежит D)

#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<locale.h>
#include<math.h>
using namespace std;

int main(){
    float u, x, y;
    setlocale(LC_ALL, "");

    cout << "¬ведите x: ";
    cin >>x;
    cout << "¬ведите y: ";
    cin >>y;

    if (((sqrt(x)+sqrt(y-1))<1) && (y<(1-sqrt(x))))
        std::cout << (u = x-y);
    else 
        std::cout << (u = x*y + 7);
    

     
return 0;
}