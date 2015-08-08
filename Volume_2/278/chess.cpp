#include <iostream>
using namespace std;

int cap(int x) {
  return x > 0 ? x : 0;
}

// straitforward: each rook will destroy one row and one column
int rook(int m, int n) {
  return m < n ? m : n;
}

// Similar to rook.
int queen(int m, int n) {
  return m < n ? m : n;
}

// The optimal way is:
// k.k.k.k
// .k.k.k.
// k.k.k.k
// .k.k.k.
// k.k.k.k
// always m > n
int knight(int m, int n) {
  if (m < n)
    return knight(n, m);
  return ((m + 1) / 2) * ((n + 1) / 2) + (m / 2) * (n / 2);
}

// The optimal way is:
// K.K.K
// .....
// K.K.K
// .....
// K.K.K
int king(int m, int n) {
  return ((m + 1) / 2) * ((n + 1) / 2);
}

int main() {
  int round;
  cin >> round;
  while (round-- > 0) {
    char c;
    int m, n;
    cin >> c >> m >> n;
    if (c == 'r') {
      cout << rook(m, n) << endl;
    } else if (c == 'k') {
      cout << knight(m, n) << endl;
    } else if (c == 'Q') {
      cout << queen(m, n) << endl;
    } else if (c == 'K') {
      cout << king(m, n) << endl;
    }
  }
}
