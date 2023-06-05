#include <iostream> // 2441000 == 2022
#include <vector>
using namespace std;

int fact(int n) {
	if ((n == 0) || (n == 1))
		return 1;
	else
		return n * fact(n - 1);
}

int main()
{ 
	setlocale(LC_ALL, "rus");
	int num; cout << "Введите число факториальной СС: "; cin >> num;
	vector<int> s;
	while (num)
	{ // Здесь мы делим наше число на массив, чтобы в будущем работать с его элементами 
		s.push_back(num % 10);
		num /= 10;
	}
	int result = 0, k = 0;
	for (auto i = s.size(); i--;) { // Проходим массив от конца до начала, умножаем каждый i-ый элемент числа на i-ый факториал и суммируем полученные значения 
		k = s[i] * fact(i);
		result += k;
	}
	cout << "Полученное число в десятичной СС: " << result;
}