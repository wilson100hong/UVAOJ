#include <iostream>
using namespace std;

int solve(int D, int I) {
  int period = 1<<(D-1); // 2 ^ (D-1)
  int index = (I-1) % period;

  int offset = 0;
  for (int i=0;i<(D-1);++i) {
    if (index &1) {
      offset += (1<<(D-2-i));
    }
    index = index >> 1;
  }
  int ans = period + offset;
  return ans;
}

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int D, I;
    // I is 1-based!
    cin >> D >> I;
    cout << solve(D, I) << endl;
  }
}
