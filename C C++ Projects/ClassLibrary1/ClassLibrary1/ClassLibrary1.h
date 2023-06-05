#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Point {
public:
	double x;
	double y;
	double z;
};
class Dekart2D : Point {
public:
	Dekart2D() {
		this->x = 0;
		this->y = 0;
	}
	Dekart2D(double x, double y) {
		this->x = x;
		this->y = y;
	}
	Dekart2D operator -(Dekart2D other) {
		Dekart2D res;
		res.x = this->x - other.x;
		res.y = this->y - other.y;
		return res;
	}
	static Dekart2D rand_val() {
		Dekart2D res;
		res.x = 1 + rand() % 9;
		res.y = 1 + rand() % 9;
		return res;
	}
	void to_str(char* bufer) {
		sprintf(bufer, "X=%.2lf;Y=%.2lf", x, y);
	}
};
class Dekart3D : Point {
public:
	double z;

	Dekart3D() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Dekart3D(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Dekart3D operator -(Dekart3D other) {
		Dekart3D res;
		res.x = this->x - other.x;
		res.y = this->y - other.y;
		res.z = this->z - other.z;
		return res;
	}
	static Dekart3D rand_val() {
		Dekart3D res;
		res.x = 1 + rand() % 9;
		res.y = 1 + rand() % 9;
		res.z = 1 + rand() % 9;
		return res;
	}
	void to_str(char* bufer) {
		sprintf(bufer, "X=%.2lf;Y=%.2lf;Z=%.2lf", x, y, z);
	}
};

//определение шаблонного класса Matrix, который позволяет хранить матрицу из объектов, которые имеются тип T
template <class T>

class Matrix {
	//определение массива элементов типа T
	T m[4][4];

public:
	Matrix() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = T::rand_val();
	}

	//запись T::rand_val() в шаблонном классе предполагает наличие у класса T публичного статического метода rand_val. Программа не может быть собрана, если у класса T нет данного метода.



	void print() {
		char* bufer = new char[100];
		printf("Matrix\n");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j].to_str3D(bufer);
				printf("%s\t", bufer);
			}
			printf("\n");
		}
		printf("\n");
		delete[] bufer;
	}

	//запись m[i][j].to_str(bufer) для элемента (он имеет тип T) массива m предполагает наличие метода to_str у класса T. Программа не может быть собрана, если у класса T нет данного метода.



	Matrix operator - (Matrix& B) {
		Matrix<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res.m[i][j] = this->m[i][j] - B.m[i][j];
		return res;
	}

	//операция сложения между экземплярами класса T (это - this->m[i][j] и b.m[i][j]) предполагает наличие у класса T перегруженного оператора сложения. Программа не может быть собрана, если у класса T нет данного перегруженного оператора.

};



//класс Substance имеет статический метод rand_val(), метод to_str() и перегруженный оператор сложения, поэтому он может быть использован в качестве параметра шаблонного класса Matrix.
template <class T>
int main() {
	int choice, CartChoice;
	cout << "Type of Matrix is 1:Cartesian (2D, 3D) or 2:Polar ?: ";
	cin >> choice;
	T = Dekart3D;
	Matrix<T> m1, m2;
	if (choice == 1) {
		cout << "2D or 3D? :";
		cin >> CartChoice;
		if (CartChoice == 1)
		{
			T = Dekart2D;
		}
		if (CartChoice == 2) {
			T = Dekart3D;
		}
		Matrix<T> m3 = m2 - m1;
		m1.print();
		m2.print();
		m3.print();
	}
}