#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void)
{
     double a, b; // input
     double alpha, beta, c; //output

     printf("a b = "); fflush(stdout);
     if (2 != scanf("%lf%lf", &a, &b)) {
	  perror(NULL);
	  exit(EXIT_FAILURE);
     }
     
     c = hypot(a, b);
     alpha = atan(a/b);
     beta = atan(b/a);

     printf("c = %f\nalpha = %f = %f deg.\nbeta = %f = %f\n",
	    c, alpha, alpha*180/M_PI, beta, beta*180/M_PI);
     return EXIT_SUCCESS;
}
