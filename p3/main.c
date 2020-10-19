#include <stdio.h>
#include <stdlib.h>
#include "funs.h"

int
main(void)
{
     printf("C2F (from, to, step) = "); fflush(stdout);
     double from, to, step;
     if (scanf("%lf%lf%lf", &from, &to, &step) == 3)
	  C2F(from, to, step);

     printf("a, b = "); fflush(stdout);
     int a, b;
     if (scanf("%d%d", &a, &b) == 2)
	  printf("sum = %d\n", sum(a, b));

     int len1;
     printf("double array len = "); fflush(stdout);
     scanf("%d", &len1);
     if (len1 < 0)
	  return EXIT_FAILURE;
     double A[len1];
     printf("array = "); fflush(stdout);
     for (int i = 0; i < len1; i++)
	  scanf("%lf", A+i);
     printf("average = %lf\n", average(A, len1));

     printf("fiblen = "); fflush(stdout);
     int len2;
     scanf("%d", &len2);
     int B[len2];
     if (len2 < 0)
	  return EXIT_FAILURE;
     fibArray(B, len2);
     for (int i = 0; i < len2; i++)
	  printf("%d ", B[i]);
     putchar('\n');

     for (int i = 0; i < len2; i++)
	  printf("%d ", fib(i));
     putchar('\n');
     return EXIT_SUCCESS;
}
