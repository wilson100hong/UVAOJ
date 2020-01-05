#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ULL;

ULL DP[30][160] = {0};

void Init() {
  for (int j=1;j<=6;++j) {
    DP[1][j] = 1;
  }
  for (int i=2;i<=24;++i) {
    for (int j=i;j<=i*6;++j) {
      for (int k=1;k<=6;++k) {
        if (j - k >= 0) {
          DP[i][j] += DP[i-1][j-k];
        }
      }
    }
  }
}

ULL gcd(ULL a, ULL b) {
  if (b == 0) return a;
  return b== 0 ? a : gcd(b, a % b);
}

int main() {
  ULL n, x;
  Init();
  while (cin >> n >> x) {
    if (n == 0 && x == 0) break;
    ULL sum = 0;
    for (int z=x;z<=n*6;++z) {
      sum += DP[n][z];
    }
    ULL denom = 1;
    for (int i=0;i<n;++i) {
      denom *= 6;
    }
    if (sum == 0) {
    }
    ULL g = gcd(denom, sum);
    ULL a = sum/g, b = denom/g;
    if (a == 0) {
      cout << 0 << endl;
    } else if (b == 1) {
      cout << a << endl;
    } else {
      cout << a << "/" << b << endl;
    }
  }
}
