#include "matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

matrix::matrix()
{
	n = 0;
	Matrix = NULL;
}

matrix::matrix(int size)
{
	n = size;
	Matrix = new double* [n];
	for(int i=0; i<n; i++){
		Matrix[i] = new double[n];}
}

matrix::matrix(char *filename)
{
	n = 0;
	ifstream infile(filename);
	while(infile){
		char buff;
		infile.get(buff);
		if(buff == '\n'){
			break;}
		if(buff == ' '){
			n++;}
	}
	infile.close();

	n++;

	Matrix = new double *[n];
	for(int i=0; i<n; i++){
		Matrix[i] = new double [n];}
	infile.open(filename);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			infile >> Matrix[i][j];}
	}
	infile.close();
}

matrix::matrix(const matrix &M)
{
	n = M.n;
	Matrix = new double* [n];
	for(int i=0; i<n; i++){
		Matrix[i] = new double[n];}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			Matrix[i][j] = M.Matrix[i][j];}
	}
}

matrix::matrix(const double M[5][5])
{
	n = 5;
	Matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		Matrix[i] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Matrix[i][j] = M[i][j];
		}
	}
}

void matrix::showVectors()
{
	for(int i=0; i<n; i++){
		cout << "x" << i+1 << " = (";
		for(int j=0; j<n; j++){
			cout << Matrix[j][i];
			if(j != n-1){
				cout << "; ";}
		}
		cout << ')' << endl;}
}

double *matrix::getPolynom()
{
	double *polynom = new double[n+1];
	polynom[0] = pow(-1, n);
	for(int i=1; i<n+1; i++){
		polynom[i] = Matrix[0][i-1] * pow(-1, n+1);}

	return polynom;
}

matrix matrix::getVectors(double *roots)
{
	matrix Vectors(n);
	matrix Y(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			Y.Matrix[j][i] = pow(roots[i], n-j-1);}
	}
	Vectors = (*this) * Y;
	return Vectors;
}

void matrix::normVectors()
{
	for(int i=0; i<n; i++){
		double sum = 0.0;
		for(int j=0; j<n; j++){
			sum += Matrix[j][i] * Matrix[j][i];}
		for(int j=0; j<n; j++){
			Matrix[j][i] /= sqrt(sum);}
	}
}

matrix matrix::toFrobenius(matrix &S)
{
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			S.Matrix[i][j] = (i == j) ? 1 : 0;}
	}
	matrix F(n);
	matrix A(n);
	A = (*this);
	for(int i=n-2; i>=0; i--){
		matrix ml(n);
		matrix mr(n);
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				ml.Matrix[j][k] = mr.Matrix[j][k] = (j == k) ? 1 : 0;}
		}
		for(int k=n-1; k>=0; k--){
			ml.Matrix[i][k] = Matrix[i+1][k];
			mr.Matrix[i][k] = (i == k) ?
				(1 / Matrix[i+1][i]) : (- Matrix[i+1][k] / Matrix[i+1][i]);}
		(*this) = ml * (*this);
		(*this) = (*this) * mr;
		S = S * mr;}
	F = (*this);
	(*this) = A;

	return F;
}

void matrix::write(char *filename)
{
	ofstream outfile(filename);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			outfile << Matrix[i][j];
			if(j != n-1){
				outfile << ' ';}
		}
		if(i != n-1){
			outfile << endl;}
	}
	outfile.close();
}

int matrix::getN()
{
	return n;
}

void matrix::operator= (const matrix &M)
{
	n = M.n;
	Matrix = new double* [n];
	for(int i=0; i<n; i++){
		Matrix[i] = new double[n];}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			Matrix[i][j] = M.Matrix[i][j];}
	}
}

matrix matrix::operator* (matrix &M)
{
	matrix matr(n);

	for(int i=0; i<n; i++){
		for(int j=0; j<M.n; j++){
			matr.Matrix[i][j] = 0;
			for(int k=0; k<M.n; k++){
				matr.Matrix[i][j] += Matrix[i][k]*M.Matrix[k][j];}
		}
	}
	return matr;
}

istream &operator>> (istream &_cin, matrix &M)
{
	for(int i=0; i<M.n; i++){
		for(int j=0; j<M.n; j++){
			_cin >> M.Matrix[i][j];}
	}

	return _cin;
}

ostream &operator<< (ostream &_cout, matrix &M)
{
	for(int i=0; i<M.n; i++){
		for(int j=0; j<M.n; j++){
			_cout << M.Matrix[i][j] << "\t";}
		_cout << "\n";
	}

	return _cout;
}

matrix::~matrix()
{
	for(int i=0; i<n; i++){
		delete [] Matrix[i];}
	delete [] Matrix;
}
