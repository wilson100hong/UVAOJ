#include <iostream>
using namespace std;

// 2016/11/08
// STAR:
// SKILL: extended euclidean
// TRAP:

typedef long long ll;

ll egcd(ll a, ll b, ll& x, ll& y) {
  if (b > a) {
    return egcd(b, a, y, x);
  }
  ll q = a/b;
  ll r = a%b;
  if (r==0) {
    x = 1;
    y = 1-q;
    return b;
  }
  ll x1, y1;
  ll g = egcd(b, r, x1, y1);
  x = y1;
  y = (x1-q*y1);
  return g;
}

ll absf(ll n) {
  return n>0 ? n : -n;
}

ll ceil(ll x, ll y) {
  return x/y + (x%y>0);
}

int main() {
  ll n;
  while (cin >> n) {
    if (n==0) break;
    ll c1, n1, c2, n2;
    cin >> c1 >> n1;
    cin >> c2 >> n2;
    ll k1, k2;
    ll g = egcd(n1, n2, k1, k2);
    if (n % g != 0) {
      cout << "failed" << endl;
      continue;
    }
    ll mul = n/g;
    k1 *= mul;
    k2 *= mul;
    // we now have k1*n1 + k2*n2 = n

    // h1*n1 == h2*n2;
    ll h1 = n2/g, h2 = n1/g;
    // decide type1 or type2 which is cheaper
    if (h1*c1 >= h2*c2) {
      // use as most as type2
      if (k1 >= 0) {
        ll q = k1/h1;
        k1 -= q*h1;
        k2 += q*h2;
      } else {
        ll q = ceil(absf(k1), h1);
        k1 += q*h1;
        k2 -= q*h2;
      }
    } else {
      // use as most as type1
      if (k2 >= 0) {
        ll q = k2/h2;
        k2 -= q*h2;
        k1 += q*h1;
      } else {
        ll q = ceil(absf(k2), h2);
        k2 += q*h2;
        k1 -= q*h1;
      }
    }
    if (k1<0 || k2<0) {
      cout << "failed" << endl;
    } else {
      cout << k1 << " " << k2 << endl;
    }
  }
}
