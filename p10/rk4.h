#ifndef RK4_H
#define RK4_H
typedef double
Derivative_d(int dim,
	     double t,
	     double conf1[static dim],
	     double df[static dim]);
typedef double
Derivative_f(int dim,
	     float t,
	     float conf1[static dim],
	     float df[static dim]);
void
rk_iter_d(int dim,
	  double dt,
	  double st1[static dim+1],
	  double st2[static dim+1],
	  Derivative_d *df);
void
rk_iter_f(int dim,
	  float dt,
	  float st1[static dim+1],
	  float st2[static dim+1],
	  Derivative_f *df);
#endif
