#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 14
#define A 16.8
#define B 32.3

double drand(double a, double b);
void fill_drand(double a, double b, int, double *);
void bubble_sort(int, double *);
void print_darr(int, const double *);

double drand(double a, double b)
{
     return a + (b-a) * rand() / RAND_MAX;
}

void bubble_sort(int n, double *p)
{
     int flag = 1;
     while (flag) {
	  flag = 0;
	  for (int i = 0; i < n-1; ++i) {
	       if (p[i] > p[i+1]) {
		    double  t = p[i];
		    p[i] = p[i+1];
		    p[i+1] = t;
		    flag = 1;
	       }
	  }
     }
}

int main(void)
{
     double arr[N], a = A, b = B;

     srand(time(NULL));
     
     fill_drand(a, b, N, arr);

     puts("before sort");
     print_darr(N, arr);
     
     bubble_sort(N, arr);

     puts("after sort");
     print_darr(N, arr);

     return 0;
}

void fill_drand(double a, double b, int n, double *p)
{
     double *e = p + n;
     while (p != e)
	  *p++ = drand(a, b);
}

void print_darr(int n, const double *p)
{
     for (int i = 0; i < n; ++i)
	  printf("%f\n", p[i]);
}
