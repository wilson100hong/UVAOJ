#include <iostream>
#include <iomanip>
#include <math.h> 
#include <sstream>
using namespace std;

#define EPS 1e-8

int p, q, r, s, t, u;

double fun(double x) {
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> p >> q >> r >> s >> t >> u;

    if (fun(0) * fun(1) > 0) {
      cout << "No solution" << endl;
      continue;
    }

    double lo = 0.0, hi = 1.0;
    while (lo + EPS < hi) {
      double x = (lo + hi) / 2;
      if (fun(lo) * fun(x) <= 0.0) {
        hi = x;
      } else {
        lo = x;
      }
    }
    double ans = (lo + hi) / 2;
    cout << fixed;
    cout << setprecision(4) << ans << endl;
  }
}
