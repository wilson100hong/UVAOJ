// 2016/10/01
// STAR: 
// SKILL: 
// TRAP:
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int F, R;
  while (1) {
    cin >> F;
    if (F == 0) break;
    cin >> R;
    vector<int> front(F, 0);
    vector<int> rear(R, 0);
    for (int i=0;i<F;++i) {
      cin >> front[i];
    }
    for (int i=0;i<R;++i) {
      cin >> rear[i];
    }
    // solve
    vector<double> ratios;
    for (int i=0;i<F;++i) {
      for (int j=0;j<R;++j) {
        double ratio = static_cast<double>(front[i]) / rear[j];
        ratios.push_back(ratio);
      }
    }
    sort(ratios.begin(), ratios.end());
    double max_q = 0.f;
    for (int i=1;i<ratios.size();++i) {
      double q = ratios[i] / ratios[i-1];
      if (q > max_q) {
        max_q = q;
      }
    }
    cout << fixed;
    cout << setprecision(2) << max_q << endl;

  }
}
