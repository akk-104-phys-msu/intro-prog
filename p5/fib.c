#include "funs.h"
#include <stdio.h>
int main(void)
{
     int n;
     if (scanf("%d", &n) == 1) {
	  int *A = create_array(n);
	  if (A)
	       print_array(A, n);
	  else
	       printf("NULL\n");
     }
     return 0;
}
