//a)а)  10 случайных целых чисел, лежащих в диапазоне от 0 до 10 включительно;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    srand(time(NULL));
    int random;
    random = printf("%d\n", rand()%10);
    return 0;
}