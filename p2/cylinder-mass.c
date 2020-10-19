/* Calculate mass of a uniform cylinder
   by surface area, heigh, and density */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


static void usage(const char *progname, FILE *);

int
main(int argc, char *argv[])
{
     double surface_area, height, density;
     
     if (argc != 4) {
	  usage(argv[0], stderr);
	  exit(EXIT_FAILURE);
     }

     surface_area = strtod(argv[1], NULL);
     height = strtod(argv[2], NULL);
     density = strtod(argv[3], NULL);
     double radius = (sqrt(height*height+2*surface_area/M_PI) - height) / 2.0;
     double volume = M_PI * radius*radius * height;

     printf("mass = %6.3lf\n", density*volume);
}

void
usage(const char *progname, FILE *fh)
{
     fprintf(fh, "%s: area height density\n"
	     "where area is the surface area of the cylinder\n",
	     progname);
}
