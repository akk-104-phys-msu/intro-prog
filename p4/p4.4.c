#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double f1(double);
static double f2(double x, double eps);
static double f3(double x, double eps);
static double f4(double x, double eps);

int
main(int argc, char *argv[])
{
	double x, eps, y1, y2, y3, y4;
	
	if (argc != 3)
		exit(EXIT_FAILURE);
	
	x	= strtod(argv[1], NULL);
	eps	= fabs(strtod(argv[2], NULL));

	if (fabs(x) > 1) {
		fprintf(stderr, "x must be outside (-1; 1): x = %lf\n", x);
		exit(EXIT_FAILURE);
	}

	y1 = f1(x);
	y2 = f2(x, eps);
	y3 = f3(x, eps);
	y4 = f4(x, eps);
	printf("%lf\n%lf\t%le\n%lf\t%le\n%lf\t%le\n",
	       y1, y2, y2/y1-1, y3, y3/y1-1, y4, y4/y1-1);
	return EXIT_SUCCESS;
}

double
f1(double x)
{
	double y = 1 - x;
	return 1/(y*y);
}

double
f2(double x, double eps)
{
	double s, t;
	int i;

	s = 0;
	for (t = i = 1; fabs(t) >= eps/i; t *= x, i++)
		s += i*t;
	printf("n2 = %d\n", i);
	return s;
}

double
f3(double x, double eps)
{
	double *A, t, s;
	long sz, i, n;

	sz = 10;
	if(!(A = malloc(sz * sizeof *A))) {
		perror(NULL);
		abort();
	}
	
	for (i = 0, t = 1; fabs((i+1)*t) > eps; i++, t*=x) {
		if (i == sz) {
			double *B;
			long nsz = sz + sz/2;
			if (!(B = realloc(A, nsz * sizeof *A))) {
				perror(NULL);
				abort();
			} else
				A = B, sz = nsz;
		}
		A[i] = (i+1)*t;
	}
	n = i-1;
	printf("n3 = %ld\n", n);
	s = 0;
	for (i = n; i >= 0; i--)
		s += A[i];
	free(A);
	return s;
}


double
f4(double x, double eps)
{
	double *A, t, sp, sn;
	long sz, i, n;

	sz = 10;
	if(!(A = malloc(sz * sizeof *A))) {
		perror(NULL);
		abort();
	}
	
	for (i = 0, t = 1; fabs((i+1)*t) > eps; i++, t*=x) {
		if (i == sz) {
			double *B;
			long nsz = sz + sz/2;
			if (!(B = realloc(A, nsz * sizeof *A))) {
				perror(NULL);
				abort();
			} else
				A = B, sz = nsz;
		}
		A[i] = (i+1)*t;
	}
	n = i-1;
	printf("n3 = %ld\n", n);
	sp = sn = 0;
	for (i = n; i >= 0; i--)
		if (A[i] >= 0)
			sp += A[i];
		else
			sn += A[i];
		
	free(A);
	return sp+sn;
}
