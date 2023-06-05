#include<string.h>
#include<math.h>
#include<conio.h>
#include<locale.h>
#include<stdlib.h>
#include<stdio.h>

struct S { int number; char stroka[20]; };

void sort(S str[4][21], int index)
{
    S resul[20];
    int i, j, k;
    //сортировка методом подсчета
    for (j = 0; j < 20; j++)
    {
        k = 0;
        for (i = 0; i < 20; i++)
        {
            if (str[index][j].number < str[index][i].number) { k++; }
        }
        resul[k] = str[index][j];
    }
    str[index][20].number = -1;
    for (k = 0; k < 20; k++)
    {
        str[index][k] = resul[k];
        printf("%4d -- %s\n", str[index][k].number, str[index][k].stroka);
    }
}


int main(void)
{
    setlocale(LC_ALL, "Russian");
    S str[4][21], result[80];

    int i, j;

    printf("               ----------------Первоначальные данные----------------\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 20; j++)
        {
            str[i][j].number = rand() % 10000;

            printf("%s",str[i][j].stroka, "%s%d%s", "abc", ((str[i][j].number) * 53 % 100), "vp");
            printf("%4d -- %s\n", str[i][j].number, str[i][j].stroka);
        }
    }

    printf("\n\n");
    printf("               ----------------Отсортированные ленты----------------\n");
    for (i = 0; i < 4; i++) {

        sort(str, i);
        printf("\n");
    }
    printf("               ----------------Конечные данные----------------\n");

    int stroka1[4] = { 0,0,0,0 }, t = 0;
    while (t < 80)
    {
        int max = 0;
        for (i = 0; i < 4; i++)
        {
            if (str[i][stroka1[i]].number > str[max][stroka1[max]].number) { max = i; }
        }
        result[t] = str[max][stroka1[max]];
        stroka1[max]++;

        printf("\n%4d -- %s", result[t].number, result[t].stroka);
        t++;
    }
    return 0;
}