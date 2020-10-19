#include <stdio.h>
#include "funs.h"

void
C2F(double from, double to, double step)
{
     for (; from <= to; from += step)
	  printf("%5.1f%8.1f\n", from, from*9/5+32);
}

int
sum(int a, int b)
{
     int r = 0;
     while (a <= b)
	  r += a++;
     return r;
}

double
average(double w[], int len)
{
     double s = 0;
     for (int i = 0; i < len; i++)
	  s += w[i];
     return s/len;
}

void
fibArray(int *fib, int len)
{
     switch (len) {
     case 0: return;
     default:
     case 2: fib[1] = 1;
     case 1: fib[0] = 0;
     }

     for (int i = 2; i < len; i++)
	  fib[i] = fib[i-1] + fib[i-2];
}

int fib(int n)
{
     if (n == 0)
	  return 0;
     else if (n == 1)
	  return 1;
     else return fib(n-1) + fib(n-2);
}
