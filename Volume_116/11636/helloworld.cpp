#include <iostream>
using namespace std;

int solve(int n) {
  int cnt = 0;
  unsigned long int base = 1;
  while (base < n) {
    base*=2;
    cnt++;
  }
  return cnt;
}

int main() {
  int cases = 1;
  int n;
  while (cin >> n) {
    if (n < 0) break;
    cout << "Case " << cases++ << ": " << solve(n) << endl;
  }
}
