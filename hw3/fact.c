#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
     long unsigned int res;
     int input;

     if (argc != 2) {
	  fprintf(stderr, "wrong number of arguments\n");
	  return EXIT_FAILURE;
     }
     
     input = atoi(argv[1]);
     for (res = 1; input > 0; input--)
	  res *= input;

     printf("%lu\n", res);
     return EXIT_SUCCESS;
}
