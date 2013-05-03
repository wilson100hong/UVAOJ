#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define PI 3.141592653589793
int main () {
  double x1, x2, x3, y1, y2, y3;
  while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
    double a1 = 2*(x1 -x2);
    double b1 = 2*(y1 -y2);
    double c1 = x1*x1 - x2*x2 + y1*y1 - y2*y2;
    double a2 = 2*(x1 -x3);
    double b2 = 2*(y1 -y3);
    double c2 = x1*x1 - x3*x3 + y1*y1 - y3*y3;
    double x = (c1*b2 - c2*b1) / (a1*b2 - a2*b1);
    double y = (c1*a2 - c2*a1) / (b1*a2 - b2*a1);
    double r2 = (x-x1)*(x-x1) + (y-y1)*(y-y1);
    double r = sqrt(r2);
    cout << setiosflags(ios::fixed)  << setprecision(2)  << 2*r*PI << endl;
  }
  return 0;
}
