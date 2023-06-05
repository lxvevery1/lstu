#include <iostream>
using namespace std;
class Base {
public:
	virtual void Input_Data() = 0;
	virtual double Func(double x) = 0;
	double result = 0;
protected:
	double a = 0, b = 0;
};
class Cos : public Base {
private:
	void Input_Data() {
		cout << "Input a, b, c: ";
		while (!(cin >> a >> b >> c) || (cin.peek() != '\n'))
			cin.clear();
		while (cin.get() != '\n');
		cout << "Invalid values! " << endl;
	}
	double Func(double x) {
		result = a * cos(b * x) + c;
		return result;
	}
	double c = 0;
};
class Pow : public Base {
private:
	void Input_Data() {
		cout << "Input a, b: ";
		while (!(cin >> a >> b) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid values! " << endl;
		}
	}
	double Func(double x) {
		result = a * pow(x, b);
		return result;
	}
};
int main() {
	int N, choice;
	double x;
	cout << "Input number of elements of the vector-function: ";
	while (!(cin >> N) || (cin.peek() != '\n') || (N <= 0)) {
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid value! " << endl;
		}
	}
	cout << "Input var x: ";
	while (!(cin >> x) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Invalid value! " << endl;
	}
	Base** Vector = new Base * [N];
	for (int i = 0; i < N; i++) {
		cout << "Type of function is 1:(a*cos(b*x)+c) or 2:(a*x^b)?: ";
		while (!(cin >> choice) || (cin.peek() != '\n') || (choice != 1) && (choice != 2))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid value! " << endl;
		}
		switch (choice) {
		case 1:
			Vector[i] = new Cos();
			Vector[i]->Input_Data();
			Vector[i]->Func(x);
			break;
		case 2:
			Vector[i] = new Pow();
			Vector[i]->Input_Data();
			Vector[i]->Func(x);
			break;
		default:
			i--;
			cout << "Invalid choise! ";
			break;
		}
	}
	for (int i = 0; i < N; i++)
		cout << "Vector[" << i << "] = " << Vector[i]->result << endl;
	for (int i = 0; i < N; i++)
		delete Vector[i];
	delete[] Vector;
}
