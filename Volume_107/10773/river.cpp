#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  int T;
  cin >> T;
  double d, v, u;
  int tc = 1;
  while (tc <= T) {
    cin >> d >> v >> u;
    cout << "Case " << tc++ << ": ";
    if (v == 0 || u == 0 || u <= v) {
      cout << "can't determine" << endl;;
      continue;
    }
    double t1 = d/u;
    double t2 = d / sqrt(u*u - v*v);
    double diff = abs(t1 - t2);
    cout << fixed << setprecision(3) << diff << endl;
  }
}
