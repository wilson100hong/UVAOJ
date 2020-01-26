#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef unsigned long long ULL;

ULL Solve(ULL a, ULL b, ULL n, ULL m) {
  if (n == 0) return a;
  if (n == 1) return b;

  ULL mod = 1;
  while (m--) {
    mod *= 10;
  }

  vector<vector<ULL>> mat(2, vector<ULL>(2, 0));
  mat[0][0] = 1;
  mat[0][1] = 1;
  mat[1][0] = 1;
  mat[1][1] = 0;


  // TODO: consider m
  n--;  // mat^(n-1)
  while (n) {
    if (n & 1) {
      ULL tb = (mat[0][0]*b  + mat[0][1]*a) % mod;
      ULL ta = (mat[1][0]*b  + mat[1][1]*a) % mod;
      b = tb;
      a = ta;
    }

    vector<vector<ULL>> tm(2, vector<ULL>(2, 0));
    tm[0][0] = (mat[0][0]*mat[0][0] + mat[0][1]*mat[1][0]) % mod;
    tm[0][1] = (mat[0][0]*mat[0][1] + mat[0][1]*mat[1][1]) % mod;
    tm[1][0] = (mat[1][0]*mat[0][0] + mat[1][1]*mat[1][0]) % mod;
    tm[1][1] = (mat[1][0]*mat[0][1] + mat[1][1]*mat[1][1]) % mod;

    mat = tm;

    n = n >> 1;
  }

  return b;
}

int main() {
  int T;
  cin >> T;
  ULL a, b, n, m;
  while (T--) {
    cin >> a >> b >> n >> m;
    cout << Solve(a, b, n, m) << endl;
  }
}
