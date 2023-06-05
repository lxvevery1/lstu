//Это задание на практике
#include <iostream>
using namespace std;

double func(double x) { return 4 - 2*pow(x, 2); } // рандомный пример

int main() {
	double a, b, c, e = 0.0001;
	cout << "Input [a;b]" << endl;
	cin >> a >> b;
	while ((b - a) > e) { // разность концов интервала > точности eps
		c = (a + b) / 2;
		if (func(c) * func(b) < 0)
			a = c;
		else
			b = c;
	}
	cout << ((a + b) / 2);
}