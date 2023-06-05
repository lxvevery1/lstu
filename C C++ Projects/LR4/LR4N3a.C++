#include <iostream>
using namespace std;
 
int main()
{
    setlocale (LC_ALL, "");
    int n,i,k,p,j,chet,i1;
    p = 0;
    k = 0;
    cout<<"¬ведите количество элементов массива: "<<"\n";
    cin >> n;
    cout<<"¬ведите элементы массива a1, a2, ..., an:" << "\n";
    int* array1 = new int [n];  //заводим массив дл€ первоначального массива который будем считывать
    for(i = 0; i < n; i++)            //заполн€ем его
        { 
        cin >> array1[i];
        }

    int* array2 = new int [n];     //массив в котором будут хранитс€ элементы без повтора
    for(i = 0; i < n; i++)
        array2[i] = 0;

    for(i = 0; i < n; i++)            //берем каждый элемент массива и провер€ем был ли он до него в массиве, если его не было, тогда записываем его в наш новый массив, если был, то пропускаем.
    {
        for(j = 0; j < i; j++)
        {
            if(array1[i] == array2[j])
            k = 1;               //счетчик повтора элемента
        }
 
        if(k == 0)
            array2[i] = array1[i];
        k=0;
    }
 
    for(i = 0; i < n; i++)
    {
        if(array2[i] != 0)
        cout << array1[i] << " ";
    }
 
    system("pause");
}