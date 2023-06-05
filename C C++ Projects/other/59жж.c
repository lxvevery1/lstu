#include <stdio.h>
#include <math.h>

int main() {
    double x, y;
    printf("x = ");                                                                            //printf = выводит значение на экран
    scanf("\n%lf", &x);                                                                        //scanf = предлагает пользователю ввести значение переменной
    printf("y = ");                                                                            //&x = ссылаться на переменную x
    scanf("\n%lf", &y);                                                                        //%lf = тип данных
    printf(fabs(x) <= 1 && y >= -2 && y <= fabs(x) ? "Yes\n" : "No\n");                        //fabs(x) - модуль числа x; ? заменяет if/else, где "Yes" выводится при выполнении условия, а "No" в остальных случаях
    return 0;                                                                                  //&& соединяет два условия (&& = И)
}