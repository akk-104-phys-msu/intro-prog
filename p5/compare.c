#include "funs.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 64
#define FMTSIZE 20

int main(void)
{
     char str1[SIZE], str2[SIZE], fmt[FMTSIZE];
     snprintf(fmt, FMTSIZE, "%%%ds", SIZE);
     scanf(fmt, str1);
     scanf(fmt, str2);
     printf("%d\n", strcompare(str1, str2));
}
