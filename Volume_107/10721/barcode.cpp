#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int LL;

constexpr LL kUndef = -1;

vector<vector<vector<LL>>> DP(51, vector<vector<LL>>(51, vector<LL>(51, kUndef)));

LL solve(int n, int k, int m) {
  if (n==0 && k==0) return 1;
  //cout << "n: " << n << " k: " << k << " m: " << m << endl;
  if (n==0 || k==0 || m==0) return 0;

  if (k > n) return 0;
  if ((n+k-1)/k > m) return 0;

  if (m==1) return n == k ? 1 : 0;

  if (DP[n][k][m] == kUndef) {
    LL sum = 0;
    for (int x = 1; x <= m; ++x) {
      sum += solve(n-x, k-1, min(m, n-x-k+2));
      DP[n][k][m] = sum;
    }
    DP[n][k][m] = sum;
  }
  //cout << "DP[" << n << "][" << k << "][" << m << "] = " << DP[n][k][m] << endl;
  //cout << "n: " << n << " k: " << k << " m: " << m << endl;
  return DP[n][k][m];
}

int main() {
  int n, k, m;
  while (cin >> n) {
    cin >> k >> m;
    cout << solve(n, k, m) << endl;
  }
}
