#pragma once
#include <iostream>

using namespace std;

class polynom
{
private:
	double *vector;
	int n;
public:
	polynom(int);
	polynom(polynom &);

	void setPolynom(double *);
	void setPolynom(double, ...);
	polynom dividing(polynom &);
	double function(double);
	double solution(double, double);

	void operator= (polynom &);
	friend ostream &operator<< (ostream &, polynom &);

	~polynom();
};

