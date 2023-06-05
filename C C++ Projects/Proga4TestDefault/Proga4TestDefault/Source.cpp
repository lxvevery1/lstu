#define _CRT_SECURE_NO_WARNINGS
#define n 4
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
using namespace std;


double Get_Rand(double min, double max) {
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}
template <class T>
class Point {
protected:
	double x = 0;
	double y = 0;
};

class Dekart2D : Point<Dekart2D> {
public:
	Dekart2D() {
		this->x = 0;
		this->y = 0;
	}

	Dekart2D operator -(Dekart2D other){
		Dekart2D res;
		res.x = this->x - other.x;
		res.y = this->y - other.y;
		return res;
	}
	static Dekart2D rand_val() {
		Dekart2D res;
		res.x = Get_Rand(0, 10);
		res.y = Get_Rand(0, 10);
		return res;
	}
	void to_str(char* bufer){
		sprintf(bufer, "X=%.2f;Y=%.2f", x, y);
	}
};
class Dekart3D : Point<Dekart3D> {
protected:
	double z;
public:
	Dekart3D() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
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
		res.x = Get_Rand(0, 10);
		res.y = Get_Rand(0, 10);
		res.z = Get_Rand(0, 10);
		return res;
	}
	void to_str(char* bufer) {
		sprintf(bufer, "X=%.2f;Y=%.2f;Z=%.2f", x, y, z);
	}
};

class Polar : Point<Polar> {
private:
	double rho; // magnitude
	double theta; // phase angle
public:
	Polar() {
		this->rho = Get_Rand(0, 9.99);
		this->theta = Get_Rand(-1, 1);
	}

	Polar operator -(Polar other) {
		Polar res;
		res.x = this->x - other.x;
		res.y = this->y - other.y;
		return res;
	}

	static Polar rand_val() {
		Polar res;
		res.x = res.rho * acos(res.theta);
		res.y = res.rho * asin(res.theta);
		return res;
	}
	void to_str(char* bufer) {
		sprintf(bufer, "X=%.2f;Y=%.2f", x, y);
	}
};

template <class T>
class Matrix {

	T m[n][n];

public:
	Matrix() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				m[i][j] = T::rand_val();
	}

	void print() {
		char* bufer = new char[100];
		printf("Matrix: \n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m[i][j].to_str(bufer);
				printf("%s\t", bufer);
			}
			printf("\n");
		}
		printf("\n");
		delete[] bufer;
	}

	Matrix operator - (Matrix& B) {
		Matrix<T> res;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				res.m[i][j] = this->m[i][j] - B.m[i][j];
		return res;
	}
};
template <class T>
void select() {
	Matrix<T> m1, m2, m3;
	m3 = m1 - m2;
	m1.print(); m2.print(); m3.print();
}

int main() {
	srand(time(0));
	size_t choice;
	cout << "Type of Matrix is 1:Cartesian 2D, 2:Cartesian 3D or 3:Polar ?: ";
	cin >> choice;
	switch (choice)
	{
		case 1: select<Dekart2D>(); break;
		case 2: select<Dekart3D>(); break;
		case 3:	select<Polar>(); break;
		default: cout << "Unexpected choice\n"; break;
	}
    return 0;
}