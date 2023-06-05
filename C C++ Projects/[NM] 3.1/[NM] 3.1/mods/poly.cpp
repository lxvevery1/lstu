//100514 poly.cpp Polynons
//
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "vUtil.h"      // разные мелкие функции
#include "poly34.h"     // solution of cubic and quartic equation
#include "dfunc1.h"		// functions of one variable f(x)
#include "poly.h"		// полиномы

//---------------------------------------------------------------------------------
polynom::polynom()
{
	size = 0;
	rRoots= cRoots = deg  =-1;
	a     = NULL;
	roots = NULL;
}
//---------------------------------------------------------------------------------
polynom::polynom(int size_)
{
	if(size_<1 || size>20) vError("polynom(%d)", size_);
	size = size_;
	a = new double[size];
	deg=-1;
	while(size_--) a[size_]=0;
	roots = NULL;
}
//---------------------------------------------------------------------------------
polynom::~polynom()
{
	delete []a;
}
//---------------------------------------------------------------------------------
void polynom::clear()					// обнулить коэффициенты
{
	for (int i = 0; i < size; i++) a[i] = 0;
	deg = -1;
	rRoots = 0;
	cRoots = 0;
}
//---------------------------------------------------------------------------------
polynom::polynom(double a0, double a1)	// a0 + a1*x
{
	size = 2;
	deg  = 1;
	a = new double[size];
	a[0] = a0;
	a[1] = a1;
	roots = NULL;
	rRoots= cRoots =-1;
}
//---------------------------------------------------------------------------------
polynom::polynom(double a0, double a1, double a2) // a0 + a1*x + a2*x^2
{
	size = 3;
	deg  = 2;
	a = new double[size];
	a[0] = a0;
	a[1] = a1;
	a[2] = a2;
	roots = NULL;
	rRoots= cRoots =-1;
}
//---------------------------------------------------------------------------------
polynom::polynom(double a0, double a1, double a2, double a3) // a0 + a1*x + a2*x^2 + a3*x^3
{
	size = 4;
	deg  = 3;
	a = new double[size];
	a[0] = a0;
	a[1] = a1;
	a[2] = a2;
	a[3] = a3;
	roots = NULL;
	rRoots= cRoots =-1;
}
//---------------------------------------------------------------------------------
polynom::polynom(double a0, double a1, double a2, double a3, double a4) // a0 + a1*x + a2*x^2 + a3*x^3 + a4*x^4
{
	size = 5;
	deg  = 4;
	a = new double[size];
	a[0] = a0;
	a[1] = a1;
	a[2] = a2;
	a[3] = a3;
	a[4] = a4;
	roots = NULL;
	rRoots= cRoots =-1;
}
//---------------------------------------------------------------------------------
void polynom::set( int k, double v)		// a[k] = v
{
	if( k<0 || k>=size ) vError("polynom::set, k=%d/%d", k, size);
	a[k] = v;
}
//---------------------------------------------------------------------------------
void polynom::calcDegree()	// найти степень
{
	for (deg = size - 1; deg >= 0; deg--)
		if (a[deg] != 0) break;
}
//---------------------------------------------------------------------------------
void polynom::setSize(int k)			// Установить размер >=k
{
	if (size >= k) return;
	if (a == NULL) {
		a = new double[k];
		clear();
		return;
	}
	// теперь размер надо увеличить, а массив сохранить
	double *a1 = a;		// прежние коэффициенты
	a = new double[k];
	for (int i = 0; i < size; i++) a[i] = a1[i];
	delete[]a1;
	size = k;
	calcDegree();
}
//---------------------------------------------------------------------------------
double polynom::A(int i)					// коэффициент при x^i
{
	if (i < 0 || i >= size) return 0;
	return a[i];
}
//---------------------------------------------------------------------------------
double polynom::v(double x)	// значение в точке
{
	double s=0;
	for( int i=deg; i>=0; i-- ) s = a[i]+x*s;
	return s;
}
double polynom::operator () (double t)
{
	//return v(t);
	double s = 0;
	for (int i = deg; i >= 0; i--) s = a[i] + t*s;
	return s;
}
//---------------------------------------------------------------------------------
double polynom::dv(double x)// значение производной в точке
{
	double s=0;
	for( int i=deg; i>0; i-- ) s = i*a[i]+x*s;
	return s;
}
//---------------------------------------------------------------------------------
double polynom::ddv(double x)// значение 2-й производной в точке
{
	double s=0;
	for( int i=deg; i>1; i-- ) s = i*(i-1)*a[i]+x*s;
	return s;
}
//---------------------------------------------------------------------------------
#define dblSWAP(a,b) { double tmp = b ; b = a ; a = tmp ; }
//#define SORT(a,bv) { if(a>b){ double tmp=b; b=a; a=tmp; }}
// возвращает количество корней
int polynom::solveR()	// найти действительные корни (только для степени 1,2,3)
{
	calcDegree();
	memRoots();
	cRoots=rRoots=0;
	if( deg<=0 ) { return 0; }
	if( deg==1 ) 
	{
		roots[0] = -a[0]/a[1];
		rRoots=1;
		cRoots=0;
		return rRoots;
	}
	if( deg==2 ) 
	{
		double discr = a[1]*a[1] - 4*a[0]*a[2];
		if( discr<0 )
		{
			rRoots=0;
			cRoots=1;
			roots[0] = -a[1]/a[2]*0.5;			// real part of the root
			roots[1] = sqrt(-discr)/a[2]*0.5;	// im.  part of the root
			return rRoots;
		}
		if( discr==0 )
		{
			roots[0] = -a[1]/a[2]*0.5;
			rRoots=1;
			cRoots=0;
			return rRoots;
		}
		// if( discr>0 )
		{
			double D = sqrt(discr);
			roots[0] = (-a[1]+D)/a[2]*0.5;
			roots[1] = (-a[1]-D)/a[2]*0.5;
			rRoots=2;
			cRoots=0;
			return rRoots;
		}
	}
	if( deg==3 ) 
	{
		rRoots = SolveP3(roots, a[0]/a[3], a[1]/a[3], a[2]/a[3]);
		cRoots = (rRoots==3? 0 : 1);
		return rRoots;
	} //if( deg==3 ) 

	if( deg==4 ) 
	{
		rRoots = SolveP4(roots, a[0]/a[4], a[1]/a[4], a[2]/a[4], a[3]/a[4]);
		cRoots = (rRoots==4? 0 : rRoots==2? 1 : 2);
		return rRoots;
	} //if( deg==4 ) 
	vError("polynom::solveR, deg=%d", deg);
	return -1;
}
//---------------------------------------------------------------------------------
double polynom::rRoot(int i)	// i-й действительный корень
{
	if( i<0 || i>=rRoots) vError("polynom::rRoot: i=%d (of %d)", i, rRoots);
	return roots[i];
}
//---------------------------------------------------------------------------------
double polynom::pRoot(int i)	// действительная часть i-го комплекстного корня
{
	if( i<0 || i>=cRoots) vError("polynom::pRoot: i=%d (of %d)", i, cRoots);
	return roots[rRoots+2*i];
}
//---------------------------------------------------------------------------------
double polynom::qRoot(int i)	// мнимая часть i-го комплекстного кореня
{
	if( i<0 || i>=cRoots) vError("polynom::qRoot: i=%d (of %d)", i, cRoots);
	return roots[rRoots+2*i+1];
}
//---------------------------------------------------------------------------------
void polynom::memRoots()	// выделить память для корней
{
	if( roots ) delete[] roots;
	roots = new double[size];
}
//---------------------------------------------------------------------------------
void polynom::add( polynom &b, double k)// this += k*b
{
	int i;
	if( deg>=b.deg )
	{
		for( i=0; i<b.deg; i++ ) a[i] += k*b.a[i];
		calcDegree();
		return;
	} 
	// степень this мала. Но, может память есть?
	if( size> b.deg )
	{	
		for( i=0; i<=deg; i++ ) a[i] += k*b.a[i];
		for( i=deg+1; i<=b.deg; i++ ) a[i] = k*b.a[i];
		deg = b.deg;
		return;
	}
	// И памяти не хватает. Выделям новую
	double *old = a;
	size = b.deg+1;
	a = new double[size];
	for( i=0; i<=deg; i++ ) a[i] = old[i] + k*b.a[i];
	for( i=deg+1; i<=b.deg; i++ ) a[i] = k*b.a[i];
	deg = b.deg;
	delete []old;
	if( roots ) { delete[] roots; roots=NULL; }

}// void polynom::add( polynom &b, double k)// this += k*b
//---------------------------------------------------------------------------------
void polynom::add( polynom &a, double ka, polynom &b, double kb)// this = ka*a + kb*b
{
	if( a.deg<b.deg ) { add(b, kb, a, ka); return; }
	// теперь a.deg >= b.deg
	if( roots ) { delete[] roots; roots=NULL; }
	size = a.deg+1;
	delete []this->a;
	this->a = new double[size];
	deg = a.deg;
	int i;
	for( i=0      ; i<=b.deg; i++ ) this->a[i] = ka*a.a[i] + kb*b.a[i];
	for( i=b.deg+1; i<=deg  ; i++ ) this->a[i] = ka*a.a[i];
	calcDegree();
}// void polynom::add( polynom &a, double ka, polynom &b, double kb)// this = ka*a + kb*b
//---------------------------------------------------------------------------------
void polynom::Binom( double a0, double a1, int d)// this = (a0 + x*a1)^d
{
	setSize(d + 1);
	clear();
	deg = d;
	int i;
	if( a0==0 )	// a1^d * x^d
	{
		for( i=0; i<d; i++ ) a[i]=0;
		a[d] = pow(a1,d);
		return;
	}
	// Now a0 !=0;
	double nu=1, de=1;	// числитель и знаменатель бином.коэфф.
	double pw = pow(a0, d);
	a[0] = pw;
	for( i=1; i<=d; i++ )
	{
		nu *= (d+1-i);
		de *= i;
		pw *= a1/a0;
		a[i] = pw*nu/de;
	}
}//void polynom::Binom( double a0, double a1, int d)// this = (a0 + x*a1)^d
//---------------------------------------------------------------------------------
void polynom::Diff ( polynom &b)	// this = Diff(b);
{
	if( roots ) { delete[] roots; roots=NULL; }
	if( size<b.deg ) 
	{
		size=b.deg+1;
		if(a) delete[]a;
		a = new double[size];
	}
	// теперь места хватит
	deg = b.deg-1;
	for( int i=0; i<=deg; i++ )
	{
		a[i] = (i+1)*b.a[i+1];
	}
}
//---------------------------------------------------------------------------------
void polynom::mul(polynom &b, polynom &c)			// this = b*c
{
	int db = b.Deg(), dc = c.Deg();
	deg = db + dc;
	this->setSize(deg);
	for (int ib = 0; ib < db; ib++)
		for (int ic = 0; ic < dc; ic++)
			a[ib + ic] += b.a[ib] * c.a[ic];
}
//---------------------------------------------------------------------------------
double polynom::NewtonStep( double x) // return x-f(x)/f'(x)
{
	if( size<1 ) vError("polynom::NewtonStep, size=%d", size );
	int n=size-1;
	double f = a[n], fp = n*a[n];
	for( int k=n-1; k>=0; k-- ) f  = f*x  +  a[k];
	for( int k=n-1; k>=1; k-- )	fp = fp*x +k*a[k];
	if( fabs(fp) <1e-14 ) return dbl_MAX;
	return x-f/fp;
}
//---------------------------------------------------------------------------------
double polynom::RBorder() // граница модулей корней
{
	calcDegree();
	if( deg<1 ) return 0;
	double ad1 = 1/a[deg];
	double r=0;
	for( int k=deg-1; k>=0; k-- )
	{
		double ab = fabs(a[k]*ad1);
		if( ab>r ) r=ab;
	}
	return r+1;
}
//---------------------------------------------------------------------------------
// f(x) mod (x^4+a*x3+b*x^2+c*x+d) = p3*x^3 + p2*x^2 + p1*x + p0
void  polynom::mod4( double A, double b, double c, double d, double &p3, double &p2, double &p1, double &p0)
{
	calcDegree();
	if( deg<4 )
	{
		p0 = a[0];
		p1 =  deg>=1 ? a[1] : 0;
		p2 =  deg>=2 ? a[2] : 0;
		p3 =  deg>=3 ? a[3] : 0;
		return;
	}
	// now deg >= 4
	p3 = a[deg  ];
	p2 = a[deg-1];
	p1 = a[deg-2];
	p0 = a[deg-3];

	for( int k= deg-4; k>=0; k-- )
	{
		double t3 = p3;
		p3 = p2  - A*t3;
		p2 = p1  - b*t3;
		p1 = p0  - c*t3;
		p0 = a[k]- d*t3;
	}
}
//---------------------------------------------------------------------------------
void polynom::HichkokStep( double &a, double &b)	// one step of Hichkok method
{
	// (x^2 + a*x + b)^2 = x^4 + 2*a*x^3 + (2*b+a^2)*x^2 + 2*a*b*x + b^2
	double p3, p2, p1, p0;
	double a2 = a*a, b2 = b*b;
	mod4( 2*a, 2*b+a2, 2*a*b, b2, p3,p2,p1,p0);
	double De = p2*p2 - 3*p2*p3*a + 2*p3*p3*a2 + b*p3*p3;
	if( fabs(De)<1e-14 ) { a=b= dbl_MAX; return; }
	double a1 = a*p3*(p3*(a2+b) - p2*a-p1) +   p2*p1 - p3*p0;
	double b1 = a*p3*(b*(p3*a-p2) -  2*p0) + b*p3*p1 + p0*p2;
	De = 1/De;
	a = a1*De; b = b1*De;
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

