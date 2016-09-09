#include <iostream>
using namespace std;

int solve(int n, int m) {
  return (n/3) * (m/3);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N >> M;
    cout << solve(N, M) << endl;
  }
}
