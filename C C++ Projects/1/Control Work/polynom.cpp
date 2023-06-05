#include "polynom.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

polynom::polynom(int n)
{
	this->n = n;
	vector = new double[n];
}

polynom::polynom(polynom &V)
{
	n = V.n;
	vector = new double[n];
	for(int i=0; i<n; i++){
		vector[i] = V.vector[i];}
}

void polynom::setPolynom(double *V)
{
	for(int i=0; i<n; i++){
		vector[i] = V[i];}
	delete [] V;
}

void polynom::setPolynom(double val, ...)
{
	va_list ap;
	va_start(ap, val);
	vector[0] = val;
	for(int i=1; i<n; i++){
		vector[i] = va_arg(ap, double);}
	va_end(ap);
}

polynom polynom::dividing(polynom &V)
{
	polynom result(n - V.n + 1);
	for(int i=0; i<n-V.n+1; i++){
		result.vector[i] = 0;}
	for(int i=0; i<n-V.n+1; i++){
		result.vector[i] = vector[i] / V.vector[0];
		for(int j=0; j<V.n; j++){
			vector[i+j] -= result.vector[i] * V.vector[j];}
	}

	return result;
}

double polynom::function(double x)
{
	double result = 0.0;
	for(int i=0; i<n; i++){
		result += pow(x, n-i-1) * vector[i];}

	return result;
}

double polynom::solution(double x, double epsilon)
{
	double x1;
	do{
		x1 = x;
		x = x - function(x) * epsilon / (function(x + epsilon) - function(x));
	}while(fabs(x1 - x) > epsilon);

	return x;
}

void polynom::operator= (polynom &V)
{
	n = V.n;
	vector = new double[n];
	for(int i=0; i<n; i++){
		vector[i] = V.vector[i];}
}

ostream &operator<< (ostream &_cout, polynom &V)
{
	for(int i=0; i<V.n; i++){
		if((V.vector[i] >= 0) && i != 0){
			_cout << " + ";}
		else if(i != 0){
			_cout << " ";}
		_cout << V.vector[i];
		if(i < V.n - 2){
			_cout << "x^" << V.n - i - 1;}
		else if(i == V.n - 2){
			_cout << "x";}
	}
	_cout << endl;

	return _cout;
}

polynom::~polynom()
{
	delete [] vector;
}
