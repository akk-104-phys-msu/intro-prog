#include <stdio.h>
#include <string.h>

void mon_mult(size_t n, double *p,
	      double a, double b)
{
     double q[n+2];
     memset(q, 0, (n+2)*sizeof *q);
     q[0] = b*p[0];
     for (int i=1; i<n+2; i++)
	  q[i] = b*p[i] + a*p[i-1];
     memcpy(p, q, (n+2)*sizeof *q);
}

void diff(size_t n, double *p)
{
     for (int i = 0; i < n; i++)
	  p[i] = (i+1)*p[i+1];
     p[n] = 0;
}

int main(void)
{
     double p[7] = {1};
     for (int i = 1; i <= 3; i++)
	  for (int j = 0; j < i; j++)
	       mon_mult(i*(i-1)/2+j, p, 1, -i);
     diff(6, p);
     for (int i = 0; i < 7; i++)
	  printf("%lf x^%d\n", p[i], i);
}
  
