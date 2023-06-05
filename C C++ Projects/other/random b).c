//b) k случайных целых чисел, лежащих в диапазоне от 0 до a включительно. Значения k и a вводятся с клавиатуры
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int random, k, a;
    srand(time(k));
    printf("Введите k, a");
    scanf("\n%d", &k, &a);
    printf("%d\n", rand()%a);
    return 0;
}