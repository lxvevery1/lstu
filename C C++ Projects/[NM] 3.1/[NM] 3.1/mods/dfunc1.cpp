// dfunc1.cpp  functions of one variable f(x)
//
//#include <stdio.h>			// для отладки только
#include <math.h>

#include "dfunc1.h"		  // functions of one variable f(x)

// from http://prografix.narod.ru

//************************* 03.12.2005 **************************************//
//
//        Поиск нуля функции на заданном интервале
//        Значения функции в ax и bx должны иметь разные знаки
//
//************************* 03.12.2005 **************************************//

#define macheps (2.2e-16)	// машинная точность double
const double goldenRatio1 = 0.5 * (sqrt(5.) - 1.);
const double goldenRatio2 = 1. - goldenRatio1;

static void  swapDbl(double &a, double &b)
{
	double tmp = a; a = b; b = tmp;
}

static inline int sign(double d)
{
	if (d > 0) return 1;
	if (d < 0) return -1;
	return 0;
}

bool zeroin(double ax, double bx, MathFunc1 & func, double tol, double & res)
{
	double fa = func(ax);
	double fb = func(bx);
	if (sign(fa) * sign(fb) > 0) return false;
	if (tol < 0) tol = 0.;
	// Присвоение начальных значений
	double a = ax;
	double b = bx;
	for (;;)
	{
		double c = a;
		double fc = fa;
		double d = b - a;
		double e = d;
m30:    if (fabs(fc) < fabs(fb))
		{
			a = b;
			b = c;
			c = a;
			fa = fb;
			fb = fc;
			fc = fa;

		}
		// Проверка сходимости
		if (fb == 0) break;
		const double tol1 = 2. * macheps * fabs(b) + 0.5 * tol;
		const double xm = 0.5 * (c - b);
		if (fabs(xm) <= tol1) break;
		// Необходима ли бисекция?
		if (fabs(e) < tol1 || fabs(fa) <= fabs(fb)) goto m70;
		{
			double p, q;
			const double s = fb / fa;
			if (a == c)
			{
				// Линейная интерполяция
				p = 2. * xm * s;
				q = 1. - s;
			}
			else
			{
				// Обратная квадратичная интерполяция
				q = fa / fc;
				const double r = fb / fc;
				p = s * (2. * xm * q * (q - r) - (b - a) * (r - 1.));
				q = (q - 1.) * (r - 1.) * (s - 1.);
			}
			if (p > 0) q = -q;
			p = fabs(p);
			// Приемлема ли интерполяция
			if (p + p >= 3.*xm*q - fabs(tol1*q)) goto m70;
			if (p >= fabs(0.5*e*q)) goto m70;
			e = d;
			d = p / q;
			goto m80;
		}
m70:    e = d = xm; // бисекция
					// Завершить шаг
m80:    a = b;
		fa = fb;
		if (fabs(d) > tol1) b += d;
		else
		{
			if (xm > 0) b += tol1;
			else        b -= tol1;
		}
		fb = func(b);
		if (sign(fb) * sign(fc) <= 0) goto m30;

	}
	res = b;
	return true;
}

//************************* 26.04.2010 **************************************//
//
//        Поиск минимума или максимума функции на заданном интервале 
//                  Комбинированный метод 
//
//************************* 26.04.2010 **************************************//
// Поиск минимума функции на заданном интервале, возвращает x, при котором достигается экстремум 
double fmin(double a, double b, MathFunc1 & func, double tol)
{
	static const double eps = sqrt(macheps) / 2048; // делителя 2048 в книге не было
	if (a > b) swapDbl(a, b);
	double a0 = a, b0 = b, fa0, fb0;
	// Присвоение начальных значений
	double d, e = 0, x, v, w, fx, fv, fw;
	x = v = w = a + goldenRatio2 * (b - a);
	fa0 = fv = func(a);
	fb0 = fw = func(b);
	fx = fv = fw = func(x);
	//printf("f(%10.5f)=%10.5f\nf(%10.5f)=%10.5f\nf(%10.5f)=%10.5f\n", a0, fa0, b0, fb0, x, fx);

	//for (int i = 0; i < 20; i++) {
	//	double t = a + i*(b - a) / 20000;
	//	printf("f(%10.5f)=%10.5f\n", t, func(t));
	//}

	// Основной цикл
	for (;;)
	{
		const double xm = 0.5 * (a + b);
		const double tol1 = eps * fabs(x) + tol / 3;
		const double tol2 = tol1 + tol1;
		// Проверить критерий окончания
		if (fabs(x - xm) + 0.5 * (b - a) <= tol2) break;
		// Парабола или золотое сечение?
		if (fabs(e) > tol1)
		{
			// Построить параболу
			double r = (x - w) * (fx - fv);
			double q = (x - v) * (fx - fw);
			double p = (x - v) * q - (x - w) * r;
			q = 2 * (q - r);
			if (q > 0) p = -p;
			q = fabs(q);
			r = e;
			e = d;
			// Приемлима ли парабола?
			if (p <= q * (a - x)) goto m40;
			if (p >= q * (b - x)) goto m40;
			if (fabs(p) >= fabs(0.5 * q * r)) goto m40;
			// Шаг параболической интерполяции
			d = p / q;
			const double u = x + d;
			// Не следует вычислять слишком близко к a или b 
			if (u - a < tol2 || b - u < tol2) d = xm < x ? -tol1 : tol1;
		}
		else
		{
			// Золотое сечение
		m40:        e = x < xm ? b - x : a - x;
			d = goldenRatio2 * e;
		}
		// Не следует вычислять слишком близко к x 
		const double u = fabs(d) >= tol1 ? x + d : d < 0 ? x - tol1 : x + tol1;
		const double fu = func(u);
		//printf("f(%10.5f)=%10.5f\n", u, fu);
		if (fu <= fx)
		{
			if (u < x) b = x;
			else         a = x;
			v = w;
			fv = fw;
			w = x;
			fw = fx;
			x = u;
			fx = fu;
		}
		else
		{
			if (u < x) a = u;
			else         b = u;
			if (fu <= fw || w == x)
			{
				v = w;
				fv = fw;
				w = u;
				fw = fu;
			}
			else
				if (fu <= fv || v == x || v == w)
				{
					v = u;
					fv = fu;
				}
		}
	}
	if (fb0 <= fx) { x = b0; fx = fb0; }
	if (fa0 <= fx) { x = a0; fx = fa0; }
	return x;
}

// Поиск максимума функции на заданном интервале, возвращает x, при котором достигается экстремум 
double fmax(double a, double b, MathFunc1 & func, double tol)
{
	static const double eps = sqrt(macheps) / 2048; // делителя 2048 в книге не было
	if (a > b) swapDbl(a, b);
	// Присвоение начальных значений
	double d, e = 0, x, v, w, fx, fv, fw;
	x = v = w = a + goldenRatio2 * (b - a);
	fx = fv = fw = func(x);
	// Основной цикл
	for (;;)
	{
		const double xm = 0.5 * (a + b);
		const double tol1 = eps * fabs(x) + tol / 3;
		const double tol2 = tol1 + tol1;
		// Проверить критерий окончания
		if (fabs(x - xm) + 0.5 * (b - a) <= tol2) break;
		// Парабола или золотое сечение?
		if (fabs(e) > tol1)
		{
			// Построить параболу
			double r = (x - w) * (fx - fv);
			double q = (x - v) * (fx - fw);
			double p = (x - v) * q - (x - w) * r;
			q = 2 * (q - r);
			if (q > 0) p = -p;
			q = fabs(q);
			r = e;
			e = d;
			// Приемлима ли парабола?
			if (p <= q * (a - x)) goto m40;
			if (p >= q * (b - x)) goto m40;
			if (fabs(p) >= fabs(0.5 * q * r)) goto m40;
			// Шаг параболической интерполяции
			d = p / q;
			const double u = x + d;
			// Не следует вычислять слишком близко к a или b 
			if (u - a < tol2 || b - u < tol2) d = xm < x ? -tol1 : tol1;
		}
		else
		{
			// Золотое сечение
		m40:        e = x < xm ? b - x : a - x;
			d = goldenRatio2 * e;
		}
		// Не следует вычислять слишком близко к x 
		const double u = fabs(d) >= tol1 ? x + d : d < 0 ? x - tol1 : x + tol1;
		const double fu = func(u);
		if (fu >= fx)
		{
			if (u < x) b = x;
			else         a = x;
			v = w;
			fv = fw;
			w = x;
			fw = fx;
			x = u;
			fx = fu;
		}
		else
		{
			if (u < x) a = u;
			else         b = u;
			if (fu >= fw || w == x)
			{
				v = w;
				fv = fw;
				w = u;
				fw = fu;
			}
			else
				if (fu >= fv || v == x || v == w)
				{
					v = u;
					fv = fu;
				}
		}
	}
	return x;
}

//-----------------------------------------------------------------------------
// Численное интегрирование методом Симпсона с удвоением количества узлов на каждом шаге
// N - количество отрезков, на которые разбивается интервал интегрирования
// N = 2,4,8,16,...		на каждом шаге умножается на 2
// h = (b-a)/N;			на каждом шаге делится на 2
// Узлы разбиения (N+1) штука:
// a,      a + h, a + 2*h, ..., a + N*h = b
// x[N,0]  x[N,1] x[N,2]        x[N,N]   
//
// sum0 - часть интегральной суммы по четным точкам
// sum1 - часть интегральной суммы по нечетным точкам
//     
//  N:	sum0*h/(3*N)                                                     sum0*h/(3*N)
//  2   f(x[N,0]) + f(x[N,N])                                            4*f(x[N,1])
//  4   f(x[N,0]) + 2*f(x[N,2]) + f(x[N,N])                              4*f(x[N,1]) + 4*f(x[N,3])
//  8   f(x[N,0]) + 2*f(x[N,2]) + 2*f(x[N,4]) + 2*f(x[N,6]) + f(x[N,N])  4*f(x[N,1]) + 4*f(x[N,3]) + 4*f(x[N,5]) + 4*f(x[N,7])
//
//  res0 - значение интеграла на предыдущем шаге
//  res1 - значение интеграла на текущем шаге
//
double Simpson(double a, double b, MathFunc1 & f, double eps)
{
	double eps1 = 5 * macheps;
	if (eps <= 0) eps = eps1;
	int N = 2;
	double h2 = b-a, h= h2*0.5;				// h2 = 2*h
	double sum0 = (f(a) + f(b))*h / 3;
	double sum1 = 4.0/3.0*(f(a+h))*h;
	double res1 = sum0 + sum1, res0=0;

	do {
		N *= 2;
		sum0 = sum0*0.5 + sum1*0.25;
		sum1 = 0;
		h2 = h; h *= 0.5;
		for (double x = a + h; x < b; x += h2)
			sum1 += f(x);
		sum1 *= h2*(2./3);
		res0 = res1;
		res1 = sum0 + sum1;
		eps1 *= 1.4;
		eps += eps1;
	} while (fabs(res0 - res1) > eps);

	return res1;
}
