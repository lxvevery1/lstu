#include <iostream>
using namespace std;

void sdvig(int* array, int sdvig, int n)
{
for (int i = sdvig; i < n-1; i++)
array[i] = array[i + 1];
}

int main()
{
    setlocale(LC_ALL, "");
    int n, delta = 0; //уменьшение массива на кол-во совпадающих чисел
    cout << "Введите количество элементов массива: ";
    cin >> n;
    int* array;
    array = (int*)malloc(sizeof (int) * n); //создаем массив
    if (!array) 
    return 1;
    cout << "Введите массив: ";
    for (int i = 0; i < n; i++)
    cin >> array[i];

    for (int i = 0; i < n; i++) // печать исходного массива
    cout << array[i] << " ";
    cout << endl;

    for (int i = 0; i < n - delta - 1; i++) //поиск совпадающих чисел
    for (int j = i+1; j < n - delta ; j++)
    {
        if (array[i] == array[j]) { sdvig(array, n, j); delta++; j--; } //если есть совпадающие числа - сдвинуть
    }

    int* check = (int*)realloc(array, sizeof(int) * (n - delta)); //освобождаем лишнюю память delta
    if (check) array = check; 
    else return 1;

    for (int i = 0; i < n - delta; i++) // вывод итога
    cout << array[i] << " ";

    free(array); //удаляем массив
}