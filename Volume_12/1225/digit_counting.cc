#include <iostream>
#include <vector>
using namespace std;

void solve(int N) {
  vector<int> ans(10, 0);
  for (int i=1;i<=N;++i) {
    int x = i;
    while (x > 0) {
      int y = x % 10;
      ans[y]++;
      x /= 10;
    }
  }

  bool first = true;
  for (int a : ans) {
    if (!first) cout << " ";
    cout << a;
    first = false;
  }
}

int main() {
  int N;
  cin >> N;
  while (N--) {
    int X;
    cin >> X;
    solve(X);
    cout << endl;
  }
}
