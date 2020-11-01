#include "roots.h"
#include <stdbool.h>
#include <math.h>

static inline double mid(double a, double b)
{
     return (a + b) / 2.0;
}

static inline bool near(double a, double b, double eps)
{
     return fabs(a - b)/(1 + fabs(a)) < eps;
}

double
bisect(dfunc f, double eps, double a, double b, int *cnt)
{
     int var;
     if (!cnt) cnt = &var;
     *cnt = 0;
     double ya = f(a), yb = f(b);
     while (!near(a, b, eps)) {
	  double m = mid(a, b), ym = f(m);
	  ++*cnt;
	  if (ya * ym <= 0)
	       b = m, yb = ym;
	  else if (yb * ym <= 0)
	       a = m, ya = ym;
	  else
	       return NAN;
     }
     return mid(a, b);
}

double
newton(dfunc f, dfunc df, double eps, double a, double b, int *cnt)
{
     double x, x0;
     *cnt = 0;
     x = mid(a, b);
     do {
	  x0 = x;
	  x = x0 - f(x0)/df(x0);
	  ++*cnt;
     } while (!near(x, x0, eps));
     return x;
}
