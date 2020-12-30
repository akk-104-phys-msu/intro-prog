#include "harmonic.h"
#include <math.h>

static double omega_d, amp_d, phi_d;
static float  omega_f, amp_f, phi_f;

void
harmonic_df_d(int dim,
	      double t,
	      double c[static HARMONIC_DIM],
	      double df[static HARMONIC_DIM])
{
     df[0] = c[1];
     df[1] = - omega_d * omega_d * c[0];
}

void
harmonic_df_f(int dim,
	      float t,
	      float c[static HARMONIC_DIM],
	      float df[static HARMONIC_DIM])
{
     df[0] = c[1];
     df[1] = - omega_d * omega_d * c[0];   
}

void
harmonic_init_d(double omega,
		double c0[static HARMONIC_DIM])
{
     omega_d = omega;
     phi_d = atan(-c0[1] / c0[0] / omega);
     amp_d = c0[0] / cos(phi_d);
}

void
harmonic_init_f(float  omega,
		flaot  c0[static HARMONIC_DIM])
{
     omega_f = omega;
     phi_f = atanf(-c0[1] / c0[0] / omega);
     amp_f = c0[0] / cosf(phi_f);

}


float energy_f(int dim, float с[static HARMONIC_DIM])
{
     
