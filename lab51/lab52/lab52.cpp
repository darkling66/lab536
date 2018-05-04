// lab52.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#define SIGN_FUNC(func, x) ((func(x) > 0)? 1 : (func(x) < 0)? -1 : 0)
#define CHECK_ROOT_TOL(func, x, e)\
if (fabs(func(x)) <= (e))\
{\
return x;\
}
#define CHECK_DIFF_SIGN(s1, s2) s1 != s2
#define PRINT_MID_STAGE
typedef double(*funct_t)(double);
int localize_root(funct_t, double, double);
double bisection(funct_t, double, double, double);
double Newton(funct_t, funct_t, double, double, double);
double func(double);
double df(double);

int main()
{
	double a = -3, b = 6, eps = 1e-8, h = 0.01;
	for (a; a < b; a += h)
	{
		if (localize_root(func, a, a + h))
		{
			printf("interv [%.3f, %.3f]\n", a, a + h);
			double x0 = bisection(func, a, a + h, eps);
			printf("koren: %lf\n", x0);
			double x2 = Newton(func, df, a, b, eps);
			printf("koren : %lf\n", x2);
		}
	}
	system("pause");
	return 0;
}


int localize_root(funct_t func, double a, double b)
{
	return SIGN_FUNC(func, a) != SIGN_FUNC(func, b);
}

double bisection(funct_t func, double a, double b, double e) {
	double c = 0;
	printf("metod_bisek\n");
	do
	{
		c = (a + b) / 2;
		int sgn1 = SIGN_FUNC(func, a);
		int sgn2 = SIGN_FUNC(func, b);
		int sgn3 = SIGN_FUNC(func, c);
#ifdef PRINT_MID_STAGE
		printf("%.5f\t%.5f\t%.5f\n", a, c, b);
		printf("%d\t%d\t%d\n", sgn1, sgn3, sgn2);

#endif
		CHECK_ROOT_TOL(func, a, e);
		CHECK_ROOT_TOL(func, c, e);
		CHECK_ROOT_TOL(func, b, e);
		if (CHECK_DIFF_SIGN(sgn1, sgn3))
		{
			b = c;
		}
		else {
			if (CHECK_DIFF_SIGN(sgn3, sgn2))
			{
				a = c;
			}
		}
	} while (fabs(a - b) > e);
	return c;
}

double Newton(funct_t func, funct_t df, double a, double b, double e) {
	printf("metod_Newton\n");
	a = b + 2 * e;
	do {
		a = b;
		b = b - func(b) / df(b);
	} while (fabs(b - a) > e);
	return b;
}

double func(double x) {
	return (x - 3)*cos(x) - 1;
}

double df(double x) {
	return cos(x) - sin(x)*(x - 3);
}