#include <iostream>
using namespace std;

// 2016/10/28
// STAR:
// SKILL:
// TRAP:

typedef long long ll;

ll f(int a, ll b) {
  // return x+1 for a*x < b
  if (b%a == 0) {
    return b/a;
  } else {
    return b/a + 1;
  }
}

int main() {
  ll n, m, c;
  while (cin >> n >> m >> c) {
    if (n==0&&m==0&&c==0) break;
    // count x0, x1.
    // xi means how many times we can shift by 2 for even (x0) and odd (x1) row
    ll x0 = f(2, m-7-(1-c));
    ll x1 = f(2, m-7-c);
    
    ll y0 = f(2, n-7);
    ll y1 = f(2, n-8);

    ll total = x0*y0 + x1*y1;
    cout << total << endl;
  }
}
