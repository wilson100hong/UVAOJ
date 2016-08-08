#include <iostream>
#include <vector>
using namespace std;

typedef long long int LL;

LL GCD(LL n1, LL n2) {
  if (n2 > n1) return GCD(n2, n1);
  if (n2 == 0) return n1;
  return GCD(n2, n1 % n2);
}

LL LCM(LL n1, LL n2) {
  LL gcd = GCD(n1, n2);
  LL k1 = n1 / gcd;
  LL k2 = n2 / gcd;
  return gcd*k1*k2;
}

void solve(const vector<LL>& coins, LL target) {
  int n = coins.size();
  LL best_top = -1, best_floor =-1;

  for (int w = 0; w < n; ++w) {
    for (int x = w+1; x < n; ++x) {
      LL lcmwx = LCM(coins[w], coins[x]);
      for (int y = x+1; y < n; ++y) {
        LL lcmwxy = LCM(lcmwx, coins[y]);
        for (int z = y+1; z < n; ++z) {
          LL lcmwxyz = LCM(lcmwxy, coins[z]);
          LL top = (target / lcmwxyz) *lcmwxyz;
          if (best_top == -1 || top > best_top) {
            best_top = top;
          }
          LL floor = ((target + (lcmwxyz-1)) / lcmwxyz) *lcmwxyz;
          if (best_floor == -1 || floor < best_floor) {
            best_floor = floor;
          }
        }
      }
    }
  }
  cout << best_top << " " << best_floor << endl;
}

int main() {
  int N, T;
  while (cin >> N >> T) {
    if (N == 0 && T == 0) break;
    vector<LL> coins;
    for (int n = 0; n < N; ++n) {
      LL c;
      cin >> c;
      coins.push_back(c);
    }

    while (T--) {
      int t;
      cin >> t;
      solve(coins, t);
    }
  }
}
