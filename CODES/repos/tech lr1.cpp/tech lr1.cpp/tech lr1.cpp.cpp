#include<iostream>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<ctime>
#include<cstdlib>
using namespace std;

struct S
{
    int number;
    char stroka[20];
};

void sort(S str[4][21], int index)
{
    S resul[20];
    int i, j, k;
    //сортировка методом пересчёта starts
    for (i = 0; i < 20; i++)
    {
        k = 0;
        for (j = 0; j < 20; j++)
        {
            if (str[index][i].number > str[index][j].number)  
            k++;
        }
        resul[k] = str[index][i];
    }
    str[index][20].number = -1;
    for (k = 0; k < 20; k++)
    {
        str[index][k] = resul[k];
        cout << str[index][k].number << str[index][k].stroka;
    }
}   //сортировка методом пересчёта ends

/*void Textgenerator(int size) {
    srand(time(NULL));

    string text;

    for (int i = 0, j = 0; i < size; i++) {
        j = rand() % 10 + 1;

        if (j > size - i) 
        j = size - i;
        i += j;

        for (int k = 0; k < j; k++) 
            text += (char)(rand() % 26 + 97);
        text += ' ';
    }
    text[text.size() - 1] = '.';

    cout << text << endl;
}*/

int main()
{
    setlocale(LC_ALL, "");
    S str[4][21], result[80];

    int i, j;
    int Length = 5;
    
    cout << "Первоначальные данные" << endl;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 20; j++)
        {
            str[i][j].number = rand() % 100;

            cout << str[i][j].stroka << (str[i][j].number) * 53 % 100 << "zxc";
            cout << str[i][j].number << str[i][j].stroka;
        }
    }

    cout << endl;
    cout << "Отсортированные ленты" << endl;
    for (i = 0; i < 4; i++) 
    {
        sort(str, i);
        cout << endl;
    }
    cout << "Конечные данные";
    int stroka1[4] = { 0,0,0,0 };
    int t = 0;
    while (t < 80)
    {
        int max = 0;
        for (i = 0; i < 4; i++)
        {
            if (str[i][stroka1[i]].number > str[max][stroka1[max]].number)
                max = i;
        }
        result[t] = str[max][stroka1[max]];
        stroka1[max]++;
        cout << result[t].number << result[t].stroka;
        t++;
    }
    system("pause");
    return 0;
}