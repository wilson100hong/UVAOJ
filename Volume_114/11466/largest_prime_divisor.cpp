// 1. Use sift to build PRIMES, much much faster
// 2. Remember count the number of prime divisor
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;

constexpr int kMax = 10000001;

LL PRIMES[kMax] = {0};

void Init() {
  PRIMES[0] = 1;
  PRIMES[1] = 1;
  for (int i=2;i*i <= kMax;++i) {
    if (PRIMES[i]) continue;  // non-prime
    for (int j=2*i;j<kMax;j+=i) {
      PRIMES[j] = 1;
    }
  }
}

LL Solve(LL x) {
  LL gd = -1;
  LL start = static_cast<LL>(sqrt(x));
  int prime_div_cnt = 0;
  for (LL i=start; i>=2; --i) {
    if (PRIMES[i] == 1) continue;
    if (x % i == 0) {
      prime_div_cnt++;
      gd = max(gd, i);
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  //cout << "x: " << x << endl;
  if (x != 1) {
    prime_div_cnt++;
    gd = max(gd, x);
  }
  return prime_div_cnt < 2 ? -1 : gd;
}

int main() {
  Init();
  LL x;
  while (cin >> x) {
    if (x == 0) break;
    cout << Solve(abs(x)) << endl;
  }
}
