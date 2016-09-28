#include <iostream>
using namespace std;

int spin(int start, int end, bool clockwise) {
  int diff;
  if (clockwise) {
    diff = start - end;
  } else {
    diff = end - start;
  }
  if (diff < 0) diff += 40;
  return diff*9;
}

int main() {
  int a, b, c, d;
  while (cin >> a >> b >> c >> d) {
    if (a==0&&b==0&&c==0&&d==0) break;
    int angles = 0;
    // 1. turn the dial clockwise 2 full turns
    angles += 720;
    // 2. stop at the first number
    angles += spin(a, b, true);
    // 3. turn the dial counter-clockwise 1 full turn
    angles += 360;
    // 4. continue turning counter-clockwise until the second number reached
    angles += spin(b, c, false);
    // 5. turn the dial clockwise again until the 3rd number is reached
    angles += spin(c, d, true);

    cout << angles << endl;
  }
}
