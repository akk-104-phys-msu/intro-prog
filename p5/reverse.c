#include "funs.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 64
#define FMTSIZE 20

int main(void)
{
     char str[SIZE], fmt[FMTSIZE];
     snprintf(fmt, FMTSIZE, "%%%ds", SIZE);
     scanf(fmt, str);
     strreverse(str);
     printf("%s\n", str);
}
