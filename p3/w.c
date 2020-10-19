#include <math.h>
#include <stdio.h>
#include <string.h>

int initArray(double w[], int len)
{
     double dx = 2*M_PI/len;
     for (int i = 0; i < len; i++)
	  w[i] = sin(i*dx);
}

int main(void)
{
     int len;
     scanf("%d", &len);

     double w[len];
     initArray(w, len);

     for (int i = 0; i < len; i++)
	  printf("%lf\n", w[i]);
}
