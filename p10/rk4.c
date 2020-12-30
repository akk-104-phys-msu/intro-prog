#include "rk4.h"
#include <string.h>
#define ORDER 4
void
rk_iter_d(int dim,
	  double dt,
	  double st1[static dim+1],
	  double st2[static dim+1],
	  Derivative_d *df)
{
     int i;
     double v[dim][ORDER], x[ORDER];
     st2[0] = st1[0] + dt;
     df(dim, st1[0], st1+1, v[0]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[0][i] / 2;
     df(dim, st1[0] + dt/2, x, v[1]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[1][i] / 2;
     df(dim, st1[0] + dt/2, x, v[2]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[2][i];
     df(dim, st1[0] + dt, x, v[3]);
     for (i = 0; i < dim; i++)
	  st2[i+1] = st1[i] + dt/6 * (v[0][i] + 2*v[1][i] + 2*v[2][i] + v[3][i]);
}
void rk_iter_f(int dim,
	       float dt,
	       float st1[static dim+1],
	       float st2[static dim+1],
	       Derivative_f *df)
{
     int i;
     float v[dim][ORDER], x[ORDER];
     st2[0] = st1[0] + dt;
     df(dim, st1[0], st1+1, v[0]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[0][i] / 2;
     df(dim, st1[0] + dt/2, x, v[1]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[1][i] / 2;
     df(dim, st1[0] + dt/2, x, v[2]);
     for (i = 0; i < ORDER; i++)
	  x[i] = st1[i+1] + dt * v[2][i];
     df(dim, st1[0] + dt, x, v[3]);
     for (i = 0; i < dim; i++)
	  st2[i+1] = st1[i] + dt/6 * (v[0][i] + 2*v[1][i] + 2*v[2][i] + v[3][i]);

}
