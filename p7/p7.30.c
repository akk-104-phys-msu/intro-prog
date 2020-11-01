#include <math.h>
#include <stdio.h>
#include "roots.h"

#define EPS_START 1e-3
#define EPS_END   1e-15
#define EPS_STEP  2

static double alpha;
static double f(double x) {
     return sin(x) - alpha*x;
}
static double df(double x) {
     return cos(x) - alpha;
}

static void test(double a, double b, double e)
{
     int c1, c2;
     double r1, r2;
     r1 = bisect(f, e, a, b, &c1);
     r2 = newton(f, df, e, a, b, &c2);
     printf("%.8le %.8lf %d %.8lf %d\n", e, r1, c1, r2, c2);
}

int
main(void)
{
     for (int i = 2; i < 5; i++) {
	  alpha = 1.0 / (1 << i);
	  printf("# run for alpha = %lf\n", alpha);
	  for (double e = EPS_START; e > EPS_END; e /= EPS_STEP)
	       for (double x = M_PI_2; x*alpha < 1; x += M_PI_2)
		    if (f(x) * f(x+M_PI_2) <= 0)
			 test(x, x+M_PI_2, e);

     }
}
