#include <iostream>
#include <cmath>
using namespace std;

#define LAYER_H sqrt(3)*0.5f

int skew_num(double bottom, double height) {
  if (height < 1 || bottom < 1.5)
    return 0;
  int layer_even = bottom;
  int layer_odd = bottom >= layer_even + 0.5 ? layer_even : layer_even-1;
  int sum = layer_even;
  height -= 1;
  bool even = false;
  while (height >= LAYER_H) {
    sum += (even ? layer_even : layer_odd);
    height -= LAYER_H;
    even = !even;
  }
  return sum;
}

int main() {
  double a, b;
  double slayer = sqrt(3);
  while (cin >> a >> b) {
    int ag = a;
    int bg = b;
    int grid = ag * bg;
    int skew = max(skew_num(a, b), skew_num(b, a));
//    cout << "skew: " << skew << endl;
    string type = (grid >= skew ? "grid" : "skew");
    cout << max(grid, skew) << " " << type << endl;
  }
}
