#include <iostream>
using namespace std;

int abs(int n) {
  return n < 0 ? -n : n;
}

int main() {
  int n;
  cin >> n;
  while (n-- > 0) {
    int a, b;
    cin >> a >> b;
    int x = (a + b) / 2;
    int y = (a - b) / 2;
    if (y < 0 || x + y != a || abs(x - y) != b) 
      cout << "impossible" << endl;
    else 
      cout << x << " " << y << endl;
  }
  return 0;
}
