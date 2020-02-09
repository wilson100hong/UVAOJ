#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef unsigned long long ULL;

vector<int> PRIMES;
constexpr int kMax = 10000001;
int IS_COMP[kMax] = {0};

void Sift() {
  for (int i=2;i*i<=kMax;++i) {
    if (IS_COMP[i]) continue;
    PRIMES.push_back(i);
    for (int j=2*i;j<kMax;j+=i) {
      IS_COMP[j] = 1;
    }
  }
}

map<int, int> Factorize(int x) {
  map<int, int> res;
  for (int p : PRIMES) {
    if (p > x) break;
    while (x % p == 0) {
      x /= p;
      res[p]++;
    }
  }

  if (x != 1) {
    res[x] = 1;
  }

  return res;
}

int Solve(int a, int c) {
  if (c % a != 0) return 0;
  int b = 1;
  auto a_f = Factorize(a);
  auto c_f = Factorize(c);
  for (const auto& c_kv : c_f) {
    int p = c_kv.first;
    int cnt = c_kv.second;
    if (a_f.count(p) == 0 || a_f[p] < cnt) {
      while (cnt--) {
        b *= p;
      }
    }
  }
  return b;
}

int main() {
  Sift();
  int T;
  cin >> T;
  while (T--) {
    ULL a, c;
    cin >> a >> c;
    ULL x = Solve(a, c);
    if (x > 0) {
      cout << x << endl;
    } else {
      cout << "NO SOLUTION" << endl;
    }
  }
}
