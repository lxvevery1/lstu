#define _USE_MATH_DEFINES                                                                 
#include <stdio.h>
#include <math.h>
// Найти площадь кольца, внутренний радиус которого равен 20, а внешний - заданному числу R(>20)
int main()
{
    double R, r;

    r = 20.0;

    do
    {
     printf("123");
     scanf("%lf", &R);
     if (R < r) printf("R must be large than r!\r\n");
    } while (R < r);
    
    double S = ((pow (R, 2.0)) - (pow (r, 2.0))) * M_PI;
     printf("S = %lf\r\n", S);
    return 0;
}