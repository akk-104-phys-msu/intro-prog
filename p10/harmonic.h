#ifndef HARMONIC_H
#define HARMONIC_H
enum { HARMONIC_DIM = 2 };
void
harmonic_init_d(double omega,
		double c0[static HARMONIC_DIM]);
void
harmonic_init_f(float  omega,
		flaot  c0[static HARMONIC_DIM]);
void
harmonic_df_d(int,
	      double t,
	      double c[static HARMONIC_DIM],
	      double df[static HARMONIC_DIM]);
void
harmonic_df_f(int,
	      float t,
	      float c[static HARMONIC_DIM],
	      float df[static HARMONIC_DIM]);
void analytic_f(int dim, float t, float c[static HARMONIC_DIM]);
void analytic_d(int dim, double t, double c[static HARMONIC_DIM]);

#endif
