#include <iomanip>
#include <iostream>
using namespace std;

#define PI 3.1415926
#define EPS 1e-5

double abs(double n) {
  return n > 0 ? n : -n;
}

double cylinder(double D, double d) {
  double x = (D - d) / 2;
  return PI*x * (d*d/4 + d*x/2 + x*x/3);
}

double volume(double D, double d) {
  return PI*(D*D*D/4 - d*d*d/4) - 2*cylinder(D, d);
}

double solve(double D, double V) {
  double l = 0.0, r = D;
  while (abs(l - r) > EPS) {
    double mid = (l + r) / 2;
    double v = volume(D, mid);
    if (v > V) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l;
}

int main() {
  int D, V;
  while (1) {
    cin >> D >> V;
    if (D == 0 && V == 0) break;
    cout << fixed;
    cout << setprecision(3) << solve(D, V) << endl;
  }
}
