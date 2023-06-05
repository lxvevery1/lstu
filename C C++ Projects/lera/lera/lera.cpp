#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>

using namespace std;

void StartInputConsole();
void EndInputConsole();

class Student
{
public:
	Student()
	{
		sirname = "";
		inicial = "";
		number = 0;

		cout << "Введите фамилию студента: ";
		StartInputConsole();
		getline(cin, sirname);
		EndInputConsole();

		cout << "Введите инициалы студента: ";
		StartInputConsole();
		getline(cin, inicial);
		EndInputConsole();

		cout << "Введите номер группы(4 цифры): ";
		cin >> number;
		cin.ignore(32767, '\n');

		for (int i = 0; i < n; i++)
		{
			int inputData = rand() % 4 + 2;
			this->uspev.at(i) = inputData;
		}
	}

	Student(string sirname, string inicial, int number)
	{
		this->sirname = sirname;
		this->inicial = inicial;
		this->number = number;

		for (int i = 0; i < n; i++)
		{
			int inputData = rand() % 4 + 2;
			this->uspev.at(i) = inputData;
		}
	}

	Student(string sirname, string inicial, int number, array<int, 5>& uspev) :Student(sirname, inicial, number)
	{
		for (int i = 0; i < 5; i++)
		{
			this->uspev.at(i) = uspev.at(i);
		}
	}

	~Student()
	{
	}

	Student(const Student& copyObject)
	{
		this->sirname = copyObject.sirname;
		this->inicial = copyObject.inicial;
		this->number = copyObject.number;
		this->uspev = copyObject.uspev;
		for (int i = 0; i < copyObject.n; i++)
		{
			this->uspev.at(i) = copyObject.uspev.at(i);
		}
	}

	void PrintStud()
	{
		cout << "Фамилия студента: " + sirname << endl;
		cout << "Инициалы студента: " + inicial << endl;
		cout << "Номер группы: АС_" << number << endl;
		cout << "Оценки студента: ";
		for (int i = 0; i < n; i++)
		{
			cout << this->uspev.at(i) << " ";
		}
		cout << "\nСредний балл студента: " << SrBal() << endl;
	}

	void SetStud(string sirname, string inicial, int number)
	{
		this->sirname = sirname;
		this->inicial = inicial;
		this->number = number;
	}

	double SrBal()
	{
		double srBal = 0.0;
		for (int i = 0; i < n; i++)
		{
			srBal += uspev.at(i);
		}
		return srBal / n;
	}

	/* Перегрузка оператора присваивания */
	Student& operator = (const Student& other)
	{

		this->sirname = other.sirname;
		this->inicial = other.inicial;
		this->number = other.number;
		this->uspev = other.uspev;
		for (int i = 0; i < other.n; i++)
		{
			this->uspev.at(i) = other.uspev.at(i);
		}
		return *this;
	}

private:
	static const int n = 5;

	string sirname;
	string inicial;
	int number;

	array<int, n > uspev;
};


int main()
{
	cout << "================================================================\n";
	cout << "================================================================\n\n";

	setlocale(LC_ALL, "");
	srand(time(NULL));
	const int N = 5;


	vector<Student> STUD;

	array<int, N> arr{ 5, 4, 5, 4, 5 };

	STUD.push_back(Student("Котиков", "С.А.", 1398));
	STUD.push_back(Student("Иванов", "И.И.", 4417));
	STUD.push_back(Student("Петров", "В.П.", 2341));
	STUD.push_back(Student("Базаров", "И.З.", 6715));
	STUD.push_back(Student("Раскольников", "Л.П.", 4567));

	STUD.push_back(Student());

	system("cls");

	for (int i = 0; i < STUD.size(); i++)
	{
		STUD.at(i).PrintStud();
		cout << endl;
	}

	cout << "================================================================\n";
	cout << "================================================================\n\n";

	_getch();
	return 0;
}


// Функции:

void StartInputConsole()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void EndInputConsole()
{
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
}
