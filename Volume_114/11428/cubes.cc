#include <iostream>
using namespace std;

typedef long long LL;

LL cube_root(LL n) {
  LL l = 1, r = n;
  while (l < r) {
    LL m = (l + r)/2;
    LL m3 = m * m * m;
    if (m3 == n) return m;
    if (m3 < n) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  return l;
}

void solve(int N) {
  for (LL y=1;y<60;++y) {
    LL y2 = y*y;
    if (3*y2 + 3*y +1 > N) break;
    // x^3 = N + y^3
    LL y3 = y2*y;
    LL x = cube_root(y3 + N);
    if (x*x*x == y3 + N) {
      cout << x << " " << y << endl;
      return;
    }
  }
  cout << "No solution" << endl;
}

int main() {
  int N;
  while (cin >> N) {
    if (N == 0) break;
    solve(N);
  }   
}
