#include <iostream>
#include <stdlib.h>
#include <locale.h>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RUS");
    int massiv[20], i, steps, summ = 0, max = INT_MIN, minus = 0, temp;
    for (i = 0; i < 20; i++) //рандомный массив
        massiv[i] = -100 + rand() % 200;
    for (i = 0; i < 20; i++)
        cout << massiv[i] << " "; 
    cout << endl;
    /////////////
    for (steps = 0; steps < 20; steps++) //сортировка методом выбора
        for (i = steps + 1; i < 20; i++)
        {
            if (massiv[steps] > massiv[i])
            {
                temp = massiv[steps];
                massiv[steps] = massiv[i];
                massiv[i] = temp;
            }
        }
    for (i = 0; i < 20; i++)
    {
        cout << massiv[i] << " ";
    }
    cout << endl;
    /////////////
    for (i = 0; i < 20; i++)  //сумма четных
    {
        if ((massiv[i] % 2) == 0)
            summ += massiv[i];
    }
    cout << summ << endl;
    /////////////
    for (i = 0; i < 20; i++) // вывод минимального отрицательного по модулю
    {
        if (massiv[i] < 0)
        {
            if (massiv[i] > max)
            max = massiv[i];
        }
    }
    cout << max << endl;
}
