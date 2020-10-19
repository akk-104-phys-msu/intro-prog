#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define G 9.82
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
	  fprintf(stderr, "%8.5g %8.5g %8.5g %8.5g\n", r_x, r_y, v_x, v_y);
     }
     return r_x;
}

int main(int argc, char *argv[])
{
     double delta, mass, k, v_0, alpha;

     if (argc != 6)
	  exit(EXIT_FAILURE);
     delta = strtod(argv[1], NULL);
     mass = strtod(argv[2], NULL);
     k = strtod(argv[3], NULL);
     v_0 = strtod(argv[4], NULL);
     alpha = M_PI/180 * strtod(argv[5], NULL);

     printf("dist %lf\n", dist(delta, mass, k, v_0, alpha));
}
