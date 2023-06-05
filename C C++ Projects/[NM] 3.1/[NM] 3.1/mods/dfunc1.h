// dfunc1.h  functions of one variable f(x)
// Взято с сайта http://prografix.narod.ru

class MathFunc1
{
public:
	//virtual double operator () (double) const = 0;
	virtual double operator () (double) = 0;
};

// Пример класса-продолжения:
/*
class Polynom5 : public MathFunc1
{
public:
	double a, b, c, d, e;

	double operator () (double t) const
	{
		return e + t * (d + t * (c + t * (b + t * (a + t))));
	}
};

*/

//************************* 03.12.2005 **************************************//
// Поиск нуля функции на заданном интервале
// Значения функции в ax и bx должны иметь разные знаки
// tol - заданная точность, 
// res - найденный корень 
bool zeroin(double ax, double bx, MathFunc1 & func, double tol, double & res);

//************************* 26.04.2010 **************************************//
// Поиск минимума или максимума функции на заданном интервале, возвращает x, при котором достигается экстремум 
double fmin(double a, double b, MathFunc1 & func, double eps);
double fmax(double a, double b, MathFunc1 & func, double eps);

// Численное интегрирование методом Симпсона с удвоением количества узлов на каждом шаге
double Simpson(double a, double b, MathFunc1 & f, double eps);
