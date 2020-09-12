#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* 
   argc[1] = a
   argc[2] = b */
int main(int argc, char *argv[])
{
     int err = 0;
     const double pi = 4*atan(1);
     char *endptra, *endptrb;
     double a, b; // input
     double alpha, beta, c; //output

     if (argc != 3) {
	  fprintf(stderr, "wrong number of arguments: %d\n", argc-1);
	  exit(EXIT_FAILURE);
     }

     a = strtod(argv[1], &endptra);
     err = errno;
     b = strtod(argv[2], &endptrb);
     err = err || errno;
     if (*endptra) {
	  fprintf(stderr, "bad character in floating number for a: %c\n", *endptra);
	  exit(EXIT_FAILURE);
     } else if (*endptrb) {
	  fprintf(stderr, "bad character in floating number for b: %c\n", *endptrb);
	  exit(EXIT_FAILURE);
     } else if (err) {
	  fprintf(stderr, "%s\n", strerror(err));
	  exit(EXIT_FAILURE);
     }

     c = hypot(a, b);
     alpha = atan(a/b);
     beta = atan(b/a);

     printf("c = %f\nalpha = %f = %f deg.\nbeta = %f = %f deg.\n",
	    c, alpha, alpha*180/pi, beta, beta*180/pi);
     return EXIT_SUCCESS;
}
