#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct CITIES 
    {
        string city;
        int year;
        int citizens;
    };
int main()
{
    setlocale(LC_ALL, "");
    int sumcitizens, maxcitizens; // суммарное кол-во жителей в городах; максимальное кол-во жителей в городе
    string mingorod, maxgorod, maxprirost; // город с наименьшим населением; город с наибольшим населением; город с самым большим приростом населени€ за последний год

    int size, i;
    cout << "¬ведите количество городов: ";
    cin >> size;
    CITIES *c = new CITIES[size];
    for (i = 0; i < size; i++)    
    {
        cout << "√ород: "; cin >> c[i].city;
        cout << "√од: "; cin >> c[i].year;
        cout << "∆ители: "; cin >> c[i].citizens;
        sumcitizens += c[i].citizens; // —умма всех жителей
    }
    maxcitizens = c[0].citizens;
    maxgorod = c[0].city;
    for (i = 0; i < size; i++) //÷икл поиска самого большого города+наибольшее население
    {
        if (c[i].citizens > maxcitizens)
        {
            maxcitizens = c[i].citizens;
            maxgorod = c[i].city;
        }
    }
    int mingorod1 = c[0].citizens;
    mingorod = c[0].city;
    for (i = 0; i < size; i++){
     //÷икл поиска самого маленького города
        if (c[i].citizens < mingorod1){
        mingorod1 = c[i].citizens;
        mingorod = c[i].city;}
    }
    cout << "суммарное кол-во жителей в городах: " << sumcitizens << endl;
    cout << "максимальное кол-во жителей в городе: " << maxcitizens << endl;
    cout << "√ород с наибольшим населением: " << maxgorod << endl;
    cout << "√ород с наименьшим населением: " << mingorod << endl;
    cout << "√ород с самым большим приростом населени€ за последний год: " << maxprirost << endl; //непон€тно немного
    system("pause");
    return 0;
}