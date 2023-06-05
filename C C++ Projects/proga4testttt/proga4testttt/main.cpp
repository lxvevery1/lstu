#include <stdio.h>

#include <math.h>

#include <vector>

#include <iostream>

using namespace std;

//¬вод с клавиатуры значени€ типа double

double inputParamFromKeyboard()

{

	double temp;

	bool success = false;

	do

	{

		cin.clear();

		//очистка буферов

		_flushall();

		cin >> temp;

		cout << endl;

		if (cin.fail())

			cout << "Incorrect input. Please try again: " << endl;

		else

			success = true;

	}

	while (!success); //контроль ввода

	return temp;

}

class Func

{

public:

	virtual double calculate(double x) = 0;

	virtual void fillParam() = 0;

	virtual void otputType() = 0;

};

class Func1 : public Func

{

public:

	double calculate(double x)

	{

		return a / x + b;

	}

	void fillParam()

	{

		cout << "Input a: ";

		a = inputParamFromKeyboard();

		cout << "Input b: ";

		b = inputParamFromKeyboard();

	}

	void otputType()

	{

		cout << a << "/x+" << b << endl;

	}

private:

	double a, b;

};

class Func2 : public Func

{

public:

	double calculate(double x)

	{

		return a * log(b * x) + c;

	}

	void fillParam()

	{

		cout << "Input a: ";

		a = inputParamFromKeyboard();

		cout << "Input b: ";

		b = inputParamFromKeyboard();

		cout << "Input c: ";

		c = inputParamFromKeyboard();

	}

	void otputType()

	{

		cout << a << "*log(" << b << "*x)+" << c << endl;

	}

private:

	double a, b, c;

};

class VectorFunction

{

public:

	void fill()

	{

		int t = 0;

		bool quit = false, success = false;

		do

		{

			int t;

			do

			{

				cin.clear();

				_flushall();

				cout << "Choose type of function: a/x+b(1), a*ln(bx)+c(2) or end of adding(0): ";

				cin >> t;

				cout << endl;

				if (cin.fail())

					cout << "Incorrect input. Please try again: ";

				else

					success = true;

			}

			while (!success);

			switch (t)

			{

			case 1:

				vect.push_back(new Func1());

				vect.at(vect.size() - 1)->fillParam();

				break;

			case 2:

				vect.push_back(new Func2());

				vect.at(vect.size() - 1)->fillParam();

				break;

			case 0:

				quit = true;

				break;

			default:

				break;

			}

		}

		while (!quit); //контроль ввода

	}

	void calculateVector(double x)

	{

		cout << "Values:" << endl;

		for (int i = 0; i < vect.size(); i++)

		{

			cout << i + 1 << ": ";

			cout << vect.at(i)->calculate(x);

			cout << endl;

		}

	}

	void outpputFuncVector()

	{

		cout << "Functions:" << endl;

		for (int i = 0; i < vect.size(); i++)

		{

			cout << i + 1 << ": ";

			vect.at(i)->otputType();

		}

	}

	~VectorFunction()

	{

		vect.~vector();

	}

private:

	vector<Func*> vect;

};

void main()

{

	bool exit = false;

	double t;

	VectorFunction vector;

	vector.fill();

	while (exit != true)

	{

		cout << "What to do: Run(1) or Exit(0)? " << endl;

		t = inputParamFromKeyboard();

		switch ((int)t)

		{

		case 1:

			vector.outpputFuncVector();

			cout << endl << "Input X: ";

			vector.calculateVector(inputParamFromKeyboard());

			break;

		case 0:

			exit = true;

			break;

		}

	}

}