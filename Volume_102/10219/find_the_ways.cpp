#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef unsigned long long ULL;

#define RANGE 501

ULL DP[RANGE][RANGE] = {};  // C(n, k)

void Init() {
  for (int n=0;n<RANGE;++n) {
    for (int k=0;k<RANGE;++k) {
      DP[n][k] = 0;
    }
  }

  for (int n=1;n<RANGE;++n) {
    DP[n][0] = DP[n][n] = 1;
  }

  for (int n=2;n<RANGE;++n) {
    for (int k=1;k<n;++k) {
      DP[n][k] = DP[n-1][k] + DP[n-1][k-1];
    }
  }
}

ULL Cnk(ULL n, ULL k) {
  //cout << "C " << n << " " << k << endl;
  //if (n < k) return 0;
  //if (n == k) return 1;
  // n > k
  //if (k == 1) return n;
  
  
  if (n < RANGE && k < RANGE) {
    return DP[n][k];
  }

  
  return Cnk(n-1, k) + Cnk(n-1, k-1);
}

int Solve(ULL n, ULL k) {
  Init();

  ULL x = Cnk(n, k);
  if (x == 0) return 1;

  // x > 0
  int d = 0;
  while (x) {
    d++;
    x /= 10;
  }
  return d;
}

int main() {
  ULL n, k;
  while (cin >> n >> k) {
    cout << Solve(n, k) << endl;
  }
}
