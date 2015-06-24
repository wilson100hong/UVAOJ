#include <iostream>
#include <sstream>
using namespace std;

typedef long long int ll;

int extgcd(ll a, ll b, ll& x, ll& y) {
  ll d = a;
  if (b == 0) {
    x = 1;
    y = 0;
  } else {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }
  return d;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    ll a, b, x, y;
    ss >> a >> b;
    int d = extgcd(a, b, x, y);
    cout << x << " " << y << " " << d << endl;
  }
}
