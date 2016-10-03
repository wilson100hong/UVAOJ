// 2016/10/02
// STAR: ****
// SKILL: math, greedy
//        proof: http://www.algorithmist.com/index.php/UVa_410
// TRAP: padding 0 to let S' == 2C, and the greedy
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

double myabs(double a) {
  return a >=0.f ? a : -a;
}

void solve(vector<int>& species, int chamber) {
  int left = 0, right = species.size()-1;
  int index = 0;
  int sum = 0;
  for (int s : species) {
    sum += s;
  }
  double avg = static_cast<double>(sum) / chamber;

  double imba = 0.f;
  while (left < right) {
    double w = 0.f;
    cout << " " << index << ":";
    if (species[left] > 0) {
      cout << " " << species[left];
      w += static_cast<double>(species[left]);
    }
    if (species[right] > 0) {
      cout << " " << species[right];
      w += static_cast<double>(species[right]);
    }
    cout << endl;
    left++; right--;
    index++;
    imba += myabs(w - avg);
  }
  cout << fixed;
  cout << "IMBALANCE = " << setprecision(5) << imba << endl;
}

int main() {
  int C, S;
  int cases = 1;
  while (cin >> C >> S) {
    vector<int> species(2*C, 0);
    for (int i=0;i<S;++i) {
      cin >> species[i];
    }
    cout << "Set #" << cases++ << endl;
    sort(species.begin(), species.end());
    solve(species, C);
    cout << endl;
  }
}
