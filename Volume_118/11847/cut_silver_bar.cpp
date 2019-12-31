#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long ULL;

int ANS[20001];

void Init() {
  ANS[0] = 0;
  int p = 0;
  int x = 1;  // 2^p
  for (int i=1; i<20001; ++i) {
    while (2*x <= i) {
      p++;
      x*=2;
    }
    // 2* x > i
    ANS[i] = p;
  }
}

int main() {
  Init();
  int n;
  while (cin >> n) {
    if (n == 0) break;
    cout << ANS[n] << endl;
  }
}
