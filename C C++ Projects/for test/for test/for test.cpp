#include <iostream>
#include <Windows.h>

using namespace std;

class Matrix
{
public:
	int Rows;
	int Cols;
	double** Data;
public:

	Matrix()
	{
		Rows = 0;
		Cols = 0;
		Data = nullptr;
	}
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
	double* operator [](const int index)
	{
		return Data[index];
	}
	~Matrix()
	{
		if (this->Data != nullptr)
		{
			for (int i = 0; i < this->Rows; i++)
			{
				delete[] Data[i];
			}
			delete[] Data;
		}
	}
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
	setlocale(LC_ALL, "Rus");
	double** Matr;
	int rows = 0, cols = 0;
	do
	{
		cout << "Введите размеры матрицы в следующем порядке: кол-во строк, кол-во столбцов: ";
		cin >> rows >> cols;
		if ((rows <= 0) || (cols <= 0))
		{
			cout << "Размеры матрицы некорректны! Повторите ввод." << endl;
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
	while ((index1 <= 0) || (index2 <= 0) || (index1 > rows || index2 > cols))
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
