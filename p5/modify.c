#include "funs.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
     int n, k, *a, *b;
     n = 10;
     if (1 != scanf("%d", &k) || k <= 0)
	  return 1;
     if (!(a = malloc(n * sizeof *a))) {
	  perror(NULL);
	  abort();
     }
     a[0] = a[n-1] = 1;
     b = modify_array(a, n, k*n, &n);
     
     printf("%p %p %d\n", a, b, n);

     return 0;
}
