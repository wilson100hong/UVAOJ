#include <iostream>
using namespace std;

void Plot(int k) {
  int m = k - 1;
  // First k lines
  for (int i = 0; i < k; ++i) {
    cout << 1;
    for (int j = 2; j <= k; ++j)
      cout << " " << i * m + j;
    cout << endl;
  }
  // For rest k - 1 group, each has k - 1 lines:
  for (int s = 0; s < k - 1; ++s) {
    for (int i = 0; i < k - 1; ++i) {
      cout << s + 2;
      // For each line rest k - 1 points
      for (int j = 0; j < k - 1; ++j) {
        int js = k + 1 + j * m;
        int out = js + (i + j * s) % m;
        cout << " " << out;
      }
      cout << endl;
    }
  }
}

int main() {
  int k;
  int first = true;
  while (cin >> k) {
    if (first)
      first = false;
    else
      cout << endl;
    Plot(k);
  }
}
