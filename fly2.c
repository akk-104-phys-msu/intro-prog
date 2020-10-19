#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define G 9.81
#define EPS 1e-6
static double m, k, v0, alpha;

static double ypos(double t);
static double xpos(double t);
static double classical_time(void);
static double bisect0(double (*f)(double), double t0, double t1);

int main(int argc, char *argv[])
{
     if (argc != 5) {
	  fprintf(stderr, "Usage: %s mass k v0 alpha\n", argv[0]);
	  exit(EXIT_FAILURE);
     }
     
     m = strtod(argv[1], NULL);
     k = strtod(argv[2], NULL);
     v0 = strtod(argv[3], NULL);
     alpha = M_PI/180 * strtod(argv[4], NULL);
     double t = bisect0(ypos, 0, 1.1*classical_time());
     printf("%f\n", xpos(t));
     return EXIT_SUCCESS;	  
}

double ypos(double t)
{
     return (-m*exp(-k*t/m)*(-G*k*t-G*m+sin(alpha)*k*v0) +
	     m*(sin(alpha)*k*v0-G*m))/(k*k);
}

double xpos(double t)
{
     return v0*m*cos(alpha)*(1-exp(-k*t/m))/k;
}

double classical_time(void)
{
     return sqrt(2*v0*sin(alpha)/G);
}

double bisect0(double (*f)(double), double t0, double t1)
{
     
     do {
	  double t = (t0+t1)/2;
	  double v0, v, v1;
	  v0 = f(t0);
	  v = f(t);
	  v1 = f(t1);
	  if (v0 < 0 && v1 < 0 ||
	      v1 > 0 && v1 > 0)
	       break;
	  else if (v0 < 0 && v >= 0 ||
		   v0 > 0 && v <= 0)
	       t1 = t;
	  else
	       t0 = t;
     } while (t1 - t0 > EPS);
     return (t0+t1)/2;
}
