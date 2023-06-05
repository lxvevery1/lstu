/*N8:  1.	Заполнение массива X вещественными числами, образующими арифметическую последовательность. Количество элементов в массиве (N) и шаг последовательности (S) заданы. Начальный элемент вводит пользователь.
  2.	Расчёт заданной функции F(X) над элементами массива X и вывод значения функции пользователю. При выводе значение функции представить в экспоненциальном формате.
  3.	Расчёт элементов массива Y по формуле Yi=G(Xi) и вывод их пользователю в виде */

#include <iostream>
#include <math.h>
using namespace std;


int main()
{
    setlocale(LC_ALL, "");

    double S = 5.5;
    int N = 13;
    double a1;
    

    cout << "Введите начальный элемент: \na1 = "; cin >> a1;

    double*X = new double[N];                                   //Массив
    cout << "3.Yi = G(X): ";
    for (int i = 0; i < N; i++)
    {
       X[i]=a1+i*S;
        {
        if (X[i] < 15.0) 
        {
            cout.precision(4);
            cout << "\ny1 " << 13 * X[i] * X[i];
        }
        else if (X[i] > 70.0)
        {
            cout.precision(4); 
            cout << "\ny3 " << sqrt(X[i] - 1.0);
        }
        else if (X[i] >= 15 && X[i] <= 70)
        { 
            cout.precision(2); 
            cout << "\ny2 " << (6 - X[i]) / (X[i] * X[i] + 5.0);
        }
        }
    }
    

double Summa = 0;                                                //Сумма всех эл. массива
    for (int i = 0; i < N; i++)
    {
    Summa = Summa + X[i];
    }
    cout << "\n2.Сумма: F(X) = " << scientific << Summa << "\n";
return 0;
}