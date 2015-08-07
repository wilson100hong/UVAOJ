#include <iostream>
using namespace std;
int max(int a, int b) {
  return a > b ? a : b;
}
int min(int a, int b) {
  return a < b ? a : b;
}

int solve(int x, int y, int z) {
  int ma = max(max(x, y), max(y, z));
  int mi = min(min(x, y), min(y, z));
  if ((x - ma) * (x - mi) != 0) {
    return x;
  }
  if ((y - ma) * (y - mi) != 0) {
    return y;
  }
  if ((z - ma) * (z - mi) != 0) {
    return z;
  }
  return -1;
}

int main() {
  int round;
  cin >> round;
  for (int t = 1; t <= round; ++t) {
    int x, y, z;
    cin >> x >> y >> z;
    cout << "Case " << t << ": " << solve(x, y, z) << endl;
  }
}
