#include <iostream>
using namespace std;

int solve(int n) {
  int drink = 0;
  int m = 0;
  // n: cola, m: empty
  while (n) {
    drink += n;
    m += n;
    n = m/3;
    m = m%3;
  }
  if (m == 2) {
    drink++;
  }
  return drink;
}

int main() {
  int N;
  while (cin >> N) {
    cout << solve(N) << endl;
  }
}
