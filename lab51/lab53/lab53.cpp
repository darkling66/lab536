// lab53.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <math.h>
#define cot  1 / tan
typedef double(*func_t)(double);
double trapezia_metod(func_t, double, double, double);
double func(double);
double result();
#define pi 3.14

int main()
{
	double a = 1, b = pi / 2, e = 1e-5, S;
	S = trapezia_metod(func, a, b, e);
	double I = result();
	printf("znaydemo integral:\nI=%f\nresult:\nI=%f\n", S, I);
	system("pause");
	return 0;
}

double trapezia_metod(func_t func, double a, double b, double e)
{
	double S = 0, h = 0.001;
	do {
		S = S + (func(a + h) + func(a))*h / 2;
		if (0.5*(func(a + h) + func(a))*h >= e) {
			a = a + h;
		}
	} while (a < b);
	return S;
}

double func(double x)
{
	return x / sin(x*x);
}

double result()
{
	return (log((cot(1 / 2))*(tan((pi * pi) / 8)))) / 2;
}