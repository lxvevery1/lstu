//Даны x, y, z. Вычислите a, b

#define _USE_MATH_DEFINES                                                                      //Определение для числа Пи (M_PI)(30 строка)
#include <stdio.h>
#include <math.h>

int main()
{
    double x, y, z;                                                                            // Присваиваем переменным тип вещественный двойной точности
                         
    printf("x = ");                                                                            //printf = выводит значение на экран
    scanf("\n%lf", &x);                                                                        //scanf = предлагает пользователю ввести значение переменной
    printf("y = ");                                                                            //&x = ссылаться на переменную x
    scanf("\n%lf", &y);
    printf("z = ");
    scanf("\n%lf", &z);                                                                           

    double a1 = (sqrt(fabs(x - 1)) - cbrt(fabs(y)))/(1 + (pow(x, 2)/2) +(pow(y, 2)/4));        //Проводим вычисления, где sqrt = квадратный корень
    double b1 = x * (atan(z) + exp(-x-3));                                                     //cbrt = кубический корень, pow = возведение в степень
                                                                                               //atan = арктангенс,        exp = число e
    double a2 = (3 + exp(y-1))/(1 + pow(x, 2) * fabs(y - tan(z)));
    double b2 = 1 + fabs(y - x) + (pow(y-x, 2)/ 2) + (pow(fabs(y-x), 3)/3);

    double a3 = ((1 + y) * (((x + (y/(pow(x, 2) + 4))))/(exp(-x-2) + (1/(pow(x, 2) + 4)))));
    double b3 = (1 + cos(y-2))/((pow(x, 4)/2) + pow(sin(z), 2));                               //cos = косинус

    double a4 = y + (x/(pow(y, 2) + fabs (pow(x, 2)/(y + (pow(x, 3)/3)))));
    double b4 = (1 + pow(tan(z/2), 2));

    double a5 = (2* cos(x - (M_PI/6)))/((1/2) + pow(sin(y),2));                                //M_PI = Число Пи, sin = синус
    double b5 = 1 + (pow(2, 2)/(3 + (pow(2, 2)/5)));

    double a6 = ((1 + pow(sin(x+y),2))/(2+fabs(x-(2*x/(1+pow(x*y, 2)))))) + x;
    double b6 = pow( cos(atan(1/z)),2);

    double a7 = log(fabs((y - sqrt(fabs(x)))*(x - (y/(z + (pow(x,2)/4))))));                   //log = Натуральный логарифм
    double b7 = x - (pow(x, 2)/1*2*3) + (pow(x, 5)/1*2*3*4*5);

    printf("a) a= %lf\n   b= %lf\n", a1, b1);                                                  //Выводим результат на экран, где %lf это тип данных для вывода
    printf("b) a= %lf\n   b= %lf\n", a2, b2);                                                  //\n = переход к следующей нижней строке
    printf("c) a= %lf\n   b= %lf\n", a3, b3);
    printf("d) a= %lf\n   b= %lf\n", a4, b4);
    printf("e) a= %lf\n   b= %lf\n", a5, b5);
    printf("f) a= %lf\n   b= %lf\n", a6, b6);
    printf("g) a= %lf\n   b= %lf\n", a7, b7);

    return 0;
}
