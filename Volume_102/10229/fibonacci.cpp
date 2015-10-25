#include <iostream>
typedef long long int LL;
using namespace std;

struct Matrix {
  LL a11;
  LL a12;
  LL a21;
  LL a22;
};

struct Column {
  LL a1;
  LL a2;
};

Matrix multi(const Matrix& m1, const Matrix& m2, LL mod) {
  Matrix m3;
  m3.a11 = ((m1.a11*m2.a11) % mod + (m1.a12*m2.a21) % mod) % mod;
  m3.a12 = ((m1.a11*m2.a12) % mod + (m1.a12*m2.a22) % mod) % mod;
  m3.a21 = ((m1.a21*m2.a11) % mod + (m1.a22*m2.a21) % mod) % mod;
  m3.a22 = ((m1.a21*m2.a12) % mod + (m1.a22*m2.a22) % mod) % mod;
  return m3;
}

Column multi(const Matrix& m, const Column& c, LL mod) {
  Column rc;
  rc.a1 = ((m.a11*c.a1) % mod + (m.a12*c.a2) % mod) % mod;
  rc.a2 = ((m.a21*c.a1) % mod + (m.a22*c.a2) % mod) % mod;
  return rc;
}

LL pow2(int m) {
  LL result = 1;
  LL base = 2;
  while (m > 0) {
    if (m & 1) {
      result *= base;
    }
    base *= base;
    m >>= 1;
  }
  return result;
}

LL solve(int n, int m) {
  LL mod = pow2(m);
  if (n == 0) return 0;
  if (n == 1) return 1;

  n--;
  Column result = {1, 0};  // Identity matrix
  Matrix base = {1, 1, 1, 0};

  while (n > 0) {
    if (n & 1) {
      result = multi(base, result, mod);
    }
    base = multi(base, base, mod);
    n >>= 1;
  }
  return result.a1;
}

int main() {
  int n, m;
  while (cin >> n) {
    cin >> m;
    cout << solve(n, m) << endl;
  }
}
