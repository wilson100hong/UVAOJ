#include <iostream>
using namespace std;
int main() {
  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;
    bool first = true;
    bool has = false;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      if (x > 0) {
        has = true;
        if (!first) {
          cout << " ";
        }
        first = false;
        cout << x;
      }
    }
    if (!has) {
      cout << "0";
    }
    cout << endl;
  }
}
