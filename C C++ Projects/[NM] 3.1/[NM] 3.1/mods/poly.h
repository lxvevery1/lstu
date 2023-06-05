//100514 poly.h Polynons
//
#ifdef POLY
#error Secondary include
#endif
#define POLY

class polynom : public MathFunc1 {
private:
	int size;		// размер массива
	int deg;		// степень, <=size-1. !Степень нулевого многочлена равна -1!
	int rRoots;		// количество действительных корней
	int cRoots;		// количество пар комплексно-сопряженных корней
					// deg = rRoots + 2*cRoots
	double *a;		// коэффициенты
	double *roots;	// корни ***


public:
	polynom();	// нулевой многочлен
	polynom(int size_);	// нулевой многочлен
	polynom(double a0, double a1);	// a0 + a1*x
	polynom(double a0, double a1, double a2); // a0 + a1*x + a2*x^2
	polynom(double a0, double a1, double a2, double a3); // a0 + a1*x + a2*x^2 + a3*x^3
	polynom(double a0, double a1, double a2, double a3, double a4); // a0 + a1*x + a2*x^2 + a3*x^3 + a4*x^4
	~polynom();
	void clear();					// обнулить коэффициенты
	void set(int k, double v);		// a[k] = v
	void setSize(int k);			// Установить размер >=k
	void calcDegree();				// найти степень

	int Deg() { return deg; }		// степень
	double A(int i);				// коэффициент при x^i
	int rRt() { return rRoots; }	// количество найденный действительных корней
	int cRt() { return cRoots; }	// количество найденный пар комплексно-сопряженных корней
	double v(double x);	// значение в точке
	double operator () (double t);
	double dv(double x);// значение производной в точке
	double ddv(double x);// значение 2-й производной в точке
	
	// возвращает количество корней
	int solveR();	// найти действительные корни (только для степени 1,2,3,4)
					// корни лежат в roots, возвращает количество корней
	double rRoot(int i);	// i-й действительный корень
	double pRoot(int i);	// действительная часть i-го комплекстного корня
	double qRoot(int i);	// мнимая часть i-го комплекстного корня
private:
	void memRoots();	// выделить память для корней

	// f(x) mod (x^4+a*x3+b*x^2+c*x+d) = p3*x^3 + p2*x^2 + p1*x + p0
	void   mod4(double A, double b, double c, double d, double &p3, double &p2, double &p1, double &p0);
public:
	void add( polynom &b, double k);			// this += k*b
	void add( polynom &a, double ka, polynom &b, double kb);// this = ka*a + kb*b
	void Binom( double a0, double a1, int d);	// this = (a0 + x*a1)^d
	void Diff ( polynom &b);					// this = Diff(b);
	void mul(polynom &b, polynom &c);			// this = b*c
											//
	double RBorder();							// граница модулей корней
	double NewtonStep( double x);				// return x-f(x)/f'(x)
	void   HichkokStep( double &a, double &b);	// one step of Hichkok method
	// еще доделать:
	// умножение разное

};



