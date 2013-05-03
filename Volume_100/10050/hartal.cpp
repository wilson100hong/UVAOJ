#include <iostream>
using namespace std;
#define MAX_N 3651
#define MAX_P 100 // 0 ~ 99
bool h[MAX_N];

int main() {
  int t, n, p;
  cin >> t;
  
  while (t-- > 0) {
    cin >> n >> p;
    for (int i = 1; i <= n; ++i)
      h[i] = false;
    while (p-- > 0) {
      int f;
      cin >> f;
      for (int i = 0; i <= n; i += f) {
        h[i] = true;
      }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
      if (i % 7 != 6 && i % 7 != 0 && h[i])
        sum++;
    }
    cout << sum << endl;
  }
  return 0;
}
