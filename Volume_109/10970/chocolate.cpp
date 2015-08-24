#include <iostream>
using namespace std;
int main() {
  int m, n;
  while (cin >> m >> n) {
    cout << (m - 1 ) + m * (n - 1) << endl;
  }
  return 0;
}
