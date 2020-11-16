#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

typedef long unsigned luint;

template<typename Func>
class RectQuadrature {
     Func func;
     double sum;
public:
     RectQuadrature(double a, double b) { sum = func(a); };
     double element(double a, double b) { return func(a); }
     void update(double s) { sum += s; }
     double value(double dx)  { return sum * dx; }
};

template<typename Func>
class TrpzQuadrature {
     Func func;
     double sum;
     double ya, yb;
public:
     TrpzQuadrature(double a, double b) {
	  ya = func(a);
	  yb = func(b);
	  sum = 0;
     }
     double element(double a, double b)  {
	  return func(a);
     }
     void update(double s) { sum += s; }
     double value(double dx) {
	  return dx / 2 * (ya + 2*sum + yb);
     }
};

template<typename Func>
class SimpsonQuadrature {
     Func func;
     double sum1, sum2;
     double ya, yb;
public:
     SimpsonQuadrature(double a, double b) {
	  ya = func(a);
	  yb = func(b);
	  sum1 = 0;
	  sum2 = 0;
     }
     double element(double a, double b) {
	  return 4*func(a);
     }
     void update(double s) {
	  double t1 = sum1, t2 = sum2;
	  sum1 = s;
	  sum2 = t1/2 + t2;
     }
     double value(double dx) {
	  return dx / 3 * (ya + sum1 + sum2 + yb);
     }
};

template<typename QS, typename Tol>
class Quadrature {
     QS qstate;
     Tol tolfun;
     int itcnt;
     double a, b, eps, dx, v1, v2;
     luint N;
     void iter() {
	  dx /= 2;
	  N *= 2;
	  double s = 0;
	  for (luint i = 1; i < N; i += 2)
	       s += qstate.element(a+i*dx, a+(i+1)*dx);
	  qstate.update(s);
	  itcnt++;
     }
public:
     double operator()() {
	  do {
	       iter();
	       v1 = v2;
	       v2 = qstate.value(dx);
	  } while (tolfun(v1, v2) >= eps);
	  return v2;
     }
     int get_iter_cnt() const { return itcnt; }
     Quadrature(double aa, double ba, double epsa)
	  :qstate{aa,ba}, a {aa}, b {ba}, eps {epsa},
	   dx {b-a}, N {1}, itcnt {0} {}
     void set_eps(double e) { eps = e; }
     double operator()(double epsa) {
	  set_eps(epsa);
	  return operator()();
     }
};

struct Func {
     double operator()(double x) {
	  return std::sin(x)/std::sqrt(x);
     };
};

struct Tolerance {
     double operator()(double x, double y) {
	  return std::fabs(x-y);
     }
};

template<typename Q>
void run(Q &q, int cnt, const std::string &name)
{
     double eps = 0.1;
     std::cout << name << ":\n";
     for (; cnt --> 0; eps/=10) {
	  std::cout
	       << std::left << std::scientific << std::setw(6)
	       << std::setprecision(1) << eps << std::right << std::fixed
	       << std::setprecision(15) << std::setw(24) << q(eps)
	       << std::setw(8) << q.get_iter_cnt() << std::endl;
     }
}
typedef Quadrature<RectQuadrature<Func>, Tolerance> Rectangle;
typedef Quadrature<TrpzQuadrature<Func>, Tolerance>  Trpz;
typedef Quadrature<SimpsonQuadrature<Func>, Tolerance> Simpson;
int main()
{
     constexpr double pi = std::atan(1) * 4;
     double a = pi / 2;
     double b = pi;

     
     Rectangle qr(a, b, 1.0);
     Trpz qt(a, b, 1.0);
     Simpson  qs(a, b, 1.0);
     run<>(qr, 8, "rectangle");
     run<>(qt, 14, "trapezoid");
     run<>(qs, 14, "simpson");
}
