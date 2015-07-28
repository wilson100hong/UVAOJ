// WATCHOUT #1: center[i] could be less than right most
// WATCHOUT #2: left most will also been updated for each new added circle
#include <iomanip>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAX 1e20

double min(double a, double b) {
  return a < b ? a : b;
}

double max(double a, double b) {
  return a > b ? a : b;
}

double rec(const vector<double>& radius,
         vector<bool>& used, 
         vector<double>& center,
         int cnt,
         double left_most,
         double right_most) {
  if (cnt == used.size()) {
    return right_most - left_most;
  }
  double ans = MAX;
  for (int i = 0; i < used.size(); ++i) {
    if (!used[i]) {
      used[i] = true;
      double new_left_most, new_right_most;
      if (cnt == 0) {
        new_left_most = -radius[i];
        new_right_most = radius[i];
        center[i] = 0.f;
      } else {
        // get center[i]
        center[i] = 0;  // WATCHOUT #1
        for (int j = 0; j < used.size(); ++j) {
          if (used[j] && j != i) {
            center[i] = max(center[i], center[j] + 2 * sqrt(radius[j] * radius[i]));
          }
        }
        new_left_most = min(left_most, center[i] - radius[i]);  // WATCHOUT #2
        new_right_most = max(right_most, center[i] + radius[i]);
      }
      ans = min(ans, rec(radius, used, center, cnt + 1, new_left_most, new_right_most));
      used[i] = false;
    }
  }
  return ans;
}

double solve(const vector<double>& radius) {
  int n = radius.size();
  vector<bool> used(n, false);
  vector<double> center(n, 0.f);
  double ans = MAX;
  return rec(radius, used, center, 0, 0.f, 0.f);
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds-- > 0) {
    int n;
    cin >> n;
    vector<double> radius;
    for (int i = 0; i < n; ++i) {
      double r;
      cin >> r;
      radius.push_back(r);
    }
    double ans = solve(radius);
    cout << fixed;
    cout << setprecision(3) << ans << endl;
  }
}
