#include <iostream>
#include <Windows.h>
#include <locale.h>

using namespace std;

class Matrix
{
public:
	int Rows; // Кол-во строк
	int Cols; // Кол-во столбцов
	double** Data; // Матрица
public:
	// Конструктор по умолчанию
	Matrix()
	{
		Rows = 0;
		Cols = 0;
		Data = NULL;
	}
	// Коструктор с параметрами
	Matrix(double** Values, int rows, int cols)
	{
		this->Cols = cols;
		this->Rows = rows;
		this->Data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			this->Data[i] = new double[cols];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->Data[i][j] = Values[i][j];
			}
		}
	}
	// Перегрузка оператора индексации
	double* operator [](const int index) // Возвращает указатель
	{
		return Data[index];
	}
	// Деструктор
	~Matrix()
	{
		if (this->Data != NULL)
		{
			for (int i = 0; i < this->Rows; i++)
			{
				delete[] Data[i];
			}
			delete[] Data;
		}
	}
	// Вывод объекта
	void Print_Matrix(string Class_Name)
	{
		if (this->Data == nullptr)
		{
			cout << "Матрица пуста." << endl;
			return;
		}
		for (int i = 0; i < this->Rows; i++)
		{
			for (int j = 0; j < this->Cols; j++)
			{
				cout << this->Data[i][j] << "  ";
			}
			cout << endl;
		}
	}
};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	double** Matr;
	int rows = 0, cols = 0;
	do
	{
		cout << "Введите размеры матрицы в следующем порядке: кол-во строк, кол-во столбцов: ";
		cin >> rows >> cols;
		if ((rows <= 0) || (cols <= 0))
		{
			cout << "Размеры матрицы некорректны!Повторите ввод." << endl;
		}
	} while ((rows <= 0) || (cols <= 0));
	Matr = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		Matr[i] = new double[cols];
	}
	cout << "Введите матрицу:" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> Matr[i][j];
		}
	}
	Matrix A(Matr, rows, cols);
	A.Print_Matrix("Матрица до изменения: ");
	int index1, index2;
	double Value;
	cout << "Введите индексы заменяемого элемента в следующем порядке: строка, столбец: ";
	cin >> index1 >> index2;
	while ((index1 <= 0) || (index2 <= 0))
	{
		cout << "Данные некорректны.Повтрите ввод" << endl;
		cin >> index1 >> index2;

	}
	cout << "Введите значение: ";
	cin >> Value;
	A[index1 - 1][index2 - 1] = Value;
	A.Print_Matrix("Матрица после изменения: ");
	for (int i = 0; i < rows; i++)
	{
		delete[] Matr[i];
	}
	delete[] Matr;
	return 0;
}
