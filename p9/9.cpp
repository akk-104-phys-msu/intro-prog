#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
constexpr long int step_initial = 2;
constexpr long int step_final = 1500;
constexpr long int max_period = 1000000000;
constexpr double pi = M_PI;
constexpr double omega = 1.0;
constexpr double A = 1.0;
constexpr double eps = 1e-5;
constexpr double period = 2 * pi / omega;
struct State_d {
     double x, v, t, e;
     State_d(double xa, double va, double ta, double e)
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
     for (long step = step_initial; step <= step_final; step *= 1.5) {
	  double dt = period / step;
	  vector<State_d> state(step);
	  long int n = 0;
	  ofstream errh("errh." + to_string(step) + ".txt");
	  //ofstream errh("/dev/null");
	  errh << "#step\t period\t initpos_error \t init_vel_err \t energy_err\n";
	  errh.precision(16);
	  for (double x = A, v = 0, t = 0, eA = 0, ev = 0, eE = 0;
	       fabs(eA) < eps && /* n < max_period */ true;
	       n++)
	  {
	       for (int i = 0; i < step; ++i) {
		    double dx1 = v, dv1 = - omega*omega*x;
		    double dx2 = v+dv1*dt/2, dv2 = -omega*omega*(x + dx1*dt/2);
		    double dx3 = v+dv2*dt/2, dv3 = -omega*omega*(x + dx2*dt/2);
		    double dx4 = v+dt*dv3, dv4 = -omega*omega*(x + dx3*dt);
		    x += dt/6 * (dx1 + 2*dx2 + 2*dx3 + dx4);
		    v += dt/6 * (dv1 + 2*dv2 + 2*dv3 + dv4);
		    t = n * period + (i+1) * dt;
		    state[i] = State_d(x, v, t, omega*omega*x*x/2 + v*v/2);
	       }
	       eA = fabs(x - A);
	       ev = fabs(v);
	       double E = omega * omega * x*x / 2 + v*v/2;
	       eE = fabs(E - A*A/2);
	       if (n % (step/10*step/10*step/10*step/1000000+1) == 1)
		    errh << n << '\t' << eA << '\t' << ev << '\t' << eE<< '\n';
	  }
	  ofstream last_osc("last." + to_string(step) + ".txt");
	  last_osc << "#time\t position\t velocity\t energy\n";
	  last_osc.precision(16);
	  for (const auto& s: state)
	  last_osc << s.t << '\t' << s.x << '\t' << s.v << '\t' << 2*s.e/A*A-1 << '\n';
	  summary.push_back(Summary {step, n});
	  cerr << step << ' ' << n << std::endl;
     }
     ofstream sum("summary.txt");
     sum << "#step iterations\n";
     for (const auto &s: summary)
	  sum << s.step << '\t' << s.count << '\t' << std::endl;
}
