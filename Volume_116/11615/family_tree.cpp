#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef unsigned long long ull;

ull NumAncestors(ull n, ull x) {
  int level = 0;
  while (x > 0) {
    x /= 2;
    level++;
  }
  return (1 << (n - level + 1)) - 1;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    ull N, A, B;
    cin >> N >> A >> B;
    ull total = (1 << N) - 1;
    ull a = NumAncestors(N, A);
    ull b = NumAncestors(N, B);
    cout << total - min(a, b) + 1 << endl;
  }
}
