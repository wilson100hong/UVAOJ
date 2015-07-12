// This problem can be transformed vector space composition.
// Take sample input as example:
//   1 2 3
//   1 11 5
//   9 4 3
//   2 3 2
//
// It is equivalent to determine whether there exist positive set {a, b, c, d, z} such that:
//   1*a + 1*b + 9*c + 2*d = z
//   2*a + 11*b + 4*c + 3*d = z
//   3*a + 5*b + 3*c + 2*d = z
//   
// Canceling z by subtracting formulas:
//   2*a + 4*b - 6*c + 0*d = 0
//   1*a + 10*b - 5*c + d = 0
//
// This can be thought as 2-D vector space:
//   a*(2, 1) + b*(4, 10) + c*(-6, -5) + d*(0, 1) = 0
// where a, b, c, d are the scalar factor of vectors (2, 1), (4, 10), (-6, -5) and (0, 1).
//
// It is required a, b, c, d should be postive integers. To achieve that, angle
// between any two adjacent vectors need to be < 180 (PI). Why? think about the
// biggest angle exists between vector v1 and v2. The positive composition of
// v1 and v2 (A*v1 + B*v2, A, B > 0) always covers another vector v3's reverse (-v3). This means
// A*v1 + B*v2 = -v3 => A*v1 + B*v2 + v3 = 0. Q.E.D.
//
#include <algorithm>
#include <iostream>
#include <math.h>
#include <utility>
#include <vector>

using namespace std;

#define PI 3.14159265

typedef pair<int, int> ii;

int main() {
  while (1) {
    int n;
    cin >> n;
    if (n == 0) 
      break;

    vector<double> angles;
    for (int i = 0; i < n; ++i) {
      int x, y, z;
      cin >> x >> y >> z;
      angles.push_back(atan2(
            static_cast<double>(y - z),
            static_cast<double>(x - z)));
    }
    sort(angles.begin(), angles.end());

    double max_angle = -100.0;
    for (int i = 1; i < angles.size(); ++i) {
      max_angle = max(max_angle, angles[i] - angles[i - 1]);
    }
    // angles[0] and angles[n-1] is special case
    max_angle = max(max_angle, 2 * PI - (angles[n - 1] - angles[0]));
    cout << (max_angle > PI ? "No" : "Yes") << endl;
  }
}
