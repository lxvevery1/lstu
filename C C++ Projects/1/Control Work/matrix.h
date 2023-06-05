#pragma once
#include <iostream>

using namespace std;

class matrix
{
public:
	double** Matrix;
	int n;
	matrix();
	matrix(int);
	matrix(char *);
	matrix(const matrix &);
	matrix(const double M[5][5]);

	void showVectors();
	double *getPolynom();
	matrix getVectors(double *);
	void normVectors();
	matrix toFrobenius(matrix &);
	void write(char *);
	int getN();

	void operator= (const matrix &);
	matrix operator* (matrix &);
	friend istream &operator>> (istream &, matrix &);
	friend ostream &operator<< (ostream &, matrix &);

	~matrix();
};

