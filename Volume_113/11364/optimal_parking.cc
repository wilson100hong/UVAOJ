#include <iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    int min = 100000, max = -1;

    int x;
    while (N--) {
      cin >> x;
      if (x < min) min = x;
      if (x > max) max = x;
    }

    int ans = (max - min) * 2;

    cout << ans << endl;
  }
}
