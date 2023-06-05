#include <iostream>
using namespace std;

class Base {
public:
	virtual void Input_Data() = 0;
	virtual double Func(double x) = 0;
	double result = 0;
protected:
	double a = 0, b = 0;
	virtual ~Base() = 0 {
	}
};

class Cos : public Base {
private:
	void Input_Data() {
		cout << "Input a, b, c: ";
		while (!(cin >> a >> b >> c) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid values! " << endl;
		}
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
	double x; int choise;
	cout << "Input number of elements of the vector-function: "; // #1
	while (!(cin >> N) || (cin.peek() != '\n') || (N <= 0)) {
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid value! " << endl;
		}
	}															// #1
	
	Base** Vector = new Base *[N];
	for (int i = 0; i < N; i++) {
		cout << "Type of function is 1:(a*cos(b*x)+c) or 2:(a*x^b)?: "; // #2
		while (!(cin >> choice) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid value! " << endl;
		}																
		switch (choice) {
		case 1:
			Vector[i] = new Cos();
			break;
		case 2:
			Vector[i] = new Pow();
			break;
		default:
			i--;
			cout << "Invalid choise! " << endl;
			break;
		}
		Vector[i]->Input_Data();
	}

	while (true) {
		cout << "Input var x: ";
		while (!(cin >> x) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n'); {
				cout << "Invalid value! " << endl;
				cout << "1:Retry again or 2:exit?" << endl;
				cin >> choice;
				switch (choice) {
				case 1:
					break;
				case 2:
					return 0;
				default:
					cout << "Invalid choise! " << endl;
					break;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			Vector[i]->Func(x);
			cout << "Vector[" << i << "] = " << Vector[i]->result << endl;
		}
	}
}