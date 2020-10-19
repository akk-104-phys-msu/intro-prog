#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define G 9.81

double
dist(double delta, double mass, double k, double v_0, double alpha)
{
     double t = 0;
     double v_x, v_y, r_x, r_y;
     v_x = v_0*cos(alpha);
     v_y = v_0*sin(alpha);
     r_x = r_y = 0;

     for (; r_y >= 0; t+=delta) {
	  r_x += v_x*delta;
	  r_y += v_y*delta;
	  v_x += -k * v_x/mass*delta;
	  v_y += - (G + k*v_y/mass)*delta;
     }
     return r_x;
}

double search(double delta, double delta_a, double m, double k, double v_0)
{
     double r_max = 0;
     double a_max = 0;
     for (double alpha = 0; alpha < M_PI/2; alpha += delta_a) {
	  double r = dist(delta, m, k, v_0, alpha);
	  if (r > r_max)
	       a_max = alpha, r_max = r;
     }
     return a_max;
}

int main(int argc, char *argv[])
{
     double mass, delta, delta_a, k, v_0;
     if (argc != 6) {
	  fprintf(stderr, "Usage: %s mass delta delta_a k v_0\n", argv[0]);
	  exit(EXIT_FAILURE);
     }
     
     mass = strtod(argv[1], NULL);
     delta = strtod(argv[2], NULL);
     delta_a = strtod(argv[3], NULL);
     k = strtod(argv[4], NULL);
     v_0 = strtod(argv[5], NULL);
/*     
     printf("mass = "); fflush(stdout);
     scanf("%lf", &mass);
     printf("delta = "); fflush(stdout);
     scanf("%lf", &delta);
     printf("delta_a = "); fflush(stdout);
     scanf("%lf", &delta_a); delta_a *= M_PI/180;
     printf("k = "); fflush(stdout);
     scanf("%lf", &k);
     printf("v_0 = "); fflush(stdout);
     scanf("%lf", &v_0);
*/
     double a = search(delta, delta_a, mass, k, v_0);
     printf("angle = %lf\n", a*180/M_PI);
}
