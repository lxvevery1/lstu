#include <iostream>
#include <vector>
using namespace std;

int a(int number, int base1, int base2) { 

    return 0;
}

int b(int number) { // Перевод из 10-ой СС в факториальную
    vector<int> S;
    int k = 1;
    while (number) { // Помещаем в массив элементы полученного числа
        S.push_back(number % k);
        number /= k;
        k++;
    }

    int result = 0;
    for (size_t i = S.size(); i--;)
    { // Складываем из нашего массива число
        auto pos = pow(10, i);
        result += S[i] * pos;
    }
    return result;
}

int c(int number, int base) { // Перевод из 10-ой СС в убывающую факториальную с заданным основанием
    vector<int> S;
    int k = base;
    while (k!=1) { // Помещаем в массив элементы полученного числа
        S.push_back(number % k);
        number /= k;
        k--;
    }

    int result = 0;
    for (size_t i = S.size(); i--;) 
    { // Складываем из нашего массива число
        auto pos = pow(10, i);
        result += S[i] * pos;
    }
    return result;
}


int main()
{
    setlocale(LC_ALL, "rus");
    int B = 2022;
    cout << "Перевод из 10-ой СС в факториальную: " << B << endl;
    cout << b(B) << endl;

    int C = 40234, degree = 8;
    cout << "Перевод из 10 - ой СС в убывающую факториальную с заданным основанием: " << C << ", " << degree << endl;
    cout << c(C, 8) << endl;
}