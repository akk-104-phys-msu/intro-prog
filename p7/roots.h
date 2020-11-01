#ifndef ROOTS_H
#define ROOTS_H
typedef double (*dfunc)(double);
double bisect(dfunc f, double eps, double a, double b, int *cnt);
double newton(dfunc f, dfunc df, double eps, double a, double b, int *cnt);
#endif
