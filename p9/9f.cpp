#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
constexpr long int step_initial = 15;
constexpr long int step_final = 150000;
constexpr long int max_period = 1000000000;
constexpr float pi = M_PI;
constexpr float omega = 1.0;
constexpr float A = 1.0;
constexpr float eps = 1e-4;
constexpr float period = 2 * pi / omega;
struct State_d {
     float x, v, t, e;
     State_d(float xa, float va, float ta, float e)
	  :x{xa}, v{va}, t{ta}, e{e} {}
     State_d() :x{0}, v{0}, t{0}, e{0} {}
};
struct Summary {
     long int step;
     long int count;
};
int main()
{
     vector<Summary> summary;
     for (long step = step_initial; step <= step_final; step *= 1.1) {
	  float dt = period / step;
	  vector<State_d> state(step);
	  long int n = 0;
	  for (float x = A, v = 0, t = 0, eA = 0, ev = 0, eE = 0;
	       n < 1 && /* n < max_period */ true;
	       n++)
	  {
	       for (int i = 0; i < step; ++i) {
		    float dx1 = v, dv1 = - omega*omega*x;
		    float dx2 = v+dv1*dt/2, dv2 = -omega*omega*(x + dx1*dt/2);
		    float dx3 = v+dv2*dt/2, dv3 = -omega*omega*(x + dx2*dt/2);
		    float dx4 = v+dt*dv3, dv4 = -omega*omega*(x + dx3*dt);
		    x += dt/6 * (dx1 + 2*dx2 + 2*dx3 + dx4);
		    v += dt/6 * (dv1 + 2*dv2 + 2*dv3 + dv4);
		    t = n * period + (i+1) * dt;
		    state[i] = State_d(x, v, t, omega*omega*x*x/2 + v*v/2);
	       }
	       eA = fabs(x - A);
	       ev = fabs(v);
	       float E = omega * omega * x*x / 2 + v*v/2;
	       eE = fabs(E - A*A/2);
	       cerr << step << '\t' << dt << '\t' << eA << '\t' << ev << '\t' << eE<< endl;
	  }
	  
     }
}
