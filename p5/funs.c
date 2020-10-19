#include "funs.h"
#include <stdlib.h>
#include <stdio.h>

int *create_array(int n)
{
     int *fib = NULL;

     if (n <= 0)
	  return NULL;
     
     if (fib = malloc(n * sizeof fib[0])) {
	  switch (n) {
	  default:
	  case 2:
	       fib[1] = 1;
	  case 1:
	       fib[0] = 0;
	  }
	  for (int i = 2; i < n; i++)
	       fib[i] = fib[i-2] + fib[i-1];
     }
     return fib;
}

int *modify_array(int *x, int n, int n2, int *res)
{
     int *y;

     if (n <= 0 || n2 <= 0)
	  return NULL;
     
     if (!x) return x;

     if (y = realloc(x, n2 * sizeof x[0])) {
	  if (res)
	       *res = n2;
	  return y;
     } else {
	  if (res)
	       *res = n;
	  return x;
     }
}

void print_array(int *x, int n)
{
     if (!x)
	  return;
     for (int *p = x; p - x < n; p++)
	  printf("%d\t%d\n", (int)(p-x), *p);
}

void free_array(int *p)
{
     free(p);
}

const char *strrchar(const char *src, char ch)
{
     const char *p;

     if (!src)
	  return NULL;
     
     for (p = src; *p; p++)
	  ;

     while (p != src && *p != ch)
	  p--;

     if (*p == ch)
	  return p;
     else
	  return NULL;
}

char *strreverse(char *s)
{
     char *p, t;
     for (p = s; *p; p++)
	  ;
     /* *p == '\0' */
     p--;
     for (char *u = s; u < p; u++, p--)
	  t = *p, *p = *u, *u = t;
     return s;
}

int strcompare(const char *s1, const char *s2)
{
     if (!s1 || !s2)
	  return 0;
     while (*s1 && *s2) {
	  if (*s1 < *s2)
	       return -1;
	  else if (*s1 == *s2)
	       s1++, s2++;
	  else
	       return +1;
     }
     if (!(*s1 || *s2))
	  return 0;
     else if (*s1)
	  return 1;
     else
	  return -1;
}
