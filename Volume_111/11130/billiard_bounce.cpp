#include <iostream>
#include <cmath>
using namespace std;
// 2016/10/28
// STAR:
// SKILL:
// TRAP: 1) ball decerlarate at constant rate!

#define PI 3.14159265

double sin2(double A) {
  double rad = A*PI/180.0;
  return sin(rad);
}

double cos2(double A) {
  double rad = A*PI/180.0;
  return cos(rad);
}

int main() {
  int a, b, v, A, s;
  while (cin >> a >> b >> v >> A >> s) {
    if (a==0&&b==0&&v==0&&A==0&&s==0) break;
    double dx = v*s*cos2(A)/2.0, dy = v*s*sin2(A)/2.0;
    int nv = 0;
    if (dx > a/2.0) {
      nv = static_cast<int>((dx - a/2.0) / a) + 1;
    }
    int nh = 0;
    if (dy > b/2.0) {
      nh = static_cast<int>((dy - b/2.0) / b) + 1;
    }
    cout << nv << " " << nh << endl;
  }
}
