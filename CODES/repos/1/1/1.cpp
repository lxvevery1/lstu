#include<string.h>
#include<math.h>
#include<locale.h>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>

struct S { int number; char stroka[20]; };
S resul[8000];  //выделение памяти с запасом
void sort(S str[20][400 + 1], int index, int N)
{
    int i, j, k;
    //сортировка методом подсчета

    for (j = 0; j < N; j++)
    {
        k = 0;
        for (i = 0; i < N; i++)
        {
            if (str[index][j].number < str[index][i].number) //проблема с сортировкой
                k++;
        }
        resul[k] = str[index][j];
    }
    for (k = 0; k < N; k++)
    {
        str[index][k] = resul[k];
        printf("%s: %4d\n", str[index][k].stroka, str[index][k].number);
    }
}

S str[20][400 + 1], result[20 * 400];
int main()
{
    int N;
    scanf_s("%d", &N);
    setlocale(LC_ALL, "");

    int i, j;

    printf("               ----------------Первоначальные данные----------------\n");
    for (i = 0; i < floor(sqrt(N)); i++)
    {
        for (j = 0; j < floor(sqrt(N)); j++)       
        {
            char key[20];
            scanf_s("%s", key, N);
            str[i][j].number = rand() % 10000;
            strcpy_s(str[i][j].stroka, key);
            printf("%s: %4d\n", str[i][j].stroka, str[i][j].number);
        }
    }
    printf("\n\n");
    printf("               ----------------Отсортированные ленты----------------\n");
    for (i = 0; i < sqrt(N); i++) 
    {
        sort(str, i, sqrt(N));
        printf("\n");
    }
    printf("               ----------------Конечные данные----------------\n");

    char stroka1[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, t = 0;
    while (t < N)
    {
        int max = 0;
        for (i = 0; i < N; i++)
        {
            if (str[i][stroka1[i]].number > str[max][stroka1[max]].number) //проблема с сортировкой
                max = i;
        }
        result[t] = str[max][stroka1[max]];
        stroka1[max]++;

        printf("\n%s: %4d", result[t].stroka, result[t].number);
        t++;
    }
    return 0;
}