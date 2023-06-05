//Даны x, y, z. Вычислите a, b

#define _USE_MATH_DEFINES                                                                   
#include <stdio.h>
#include <math.h>

int main()
{
    double x, y, z;
    printf("x = ");                                                                            //printf = выводит значение на экран
    scanf("\n%lf", &x);                                                                        //scanf = предлагает пользователю ввести значение переменной
    printf("y = ");                                                                            //&x = ссылаться на переменную x
    scanf("\n%lf", &y);
    printf("z = ");
    scanf("\n%lf", &z);

    double a = ((1 + pow(sin(x+y),2))/(2+fabs(x-(2*x/(1+pow(x*y, 2)))))) + x;
    double b = pow( cos(atan(1/z)),2);  

    printf("a = %lf\nb = %lf\n", a, b);                                                  //Выводим результат на экран, где %lf это тип данных для вывода                                                //\n = переход к следующей нижней строке
    return 0;
}
