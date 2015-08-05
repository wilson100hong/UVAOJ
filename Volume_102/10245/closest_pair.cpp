// Vector copy is enpensive... very expensive.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define INF 1e10

struct Point{
  double x;
  double y;
};
bool by_x(const Point& p1, const Point& p2) { return p1.x < p2.x; }
bool by_y(const Point& p1, const Point& p2) { return p1.y < p2.y; }

inline double pow2(double n) { return n*n; }

double dist2(const Point& p1, const Point& p2) {
  return pow2(p1.x-p2.x) + pow2(p1.y-p2.y);
}

// Brute force
// [start, end)
double closest_pair(const vector<Point>& pts, int start, int end) {
  double ans = INF;
  for (int i = start; i < end - 1; ++i) {
    for (int j = i + 1; j < end; ++j) {
      double d2 = dist2(pts[i], pts[j]);
      if (d2 < ans) ans = d2;
    }
  }
  return ans;
}

// divide and conqure
double closest_pair(const vector<Point>& s_x, int start, int end, const vector<Point>& s_y) {

  //if (s_x.size() <= 3) {
  if (end - start <= 3) {
    return closest_pair(s_x, start, end);
  }
  
  int mid = (end + start) / 2;
  vector<Point> s_y_left, s_y_right;
  for (const Point& p : s_y) {
    if (p.x < s_x[mid].x) {
      s_y_left.push_back(p);
    } else {
      s_y_right.push_back(p);
    }
  }
  double d2_min = closest_pair(s_x, start, mid, s_y_left);
  double d2_right = closest_pair(s_x, mid, end, s_y_right);
  if (d2_right < d2_min)
    d2_min = d2_right;
  double ans = d2_min;
  for (int i = 0; i < s_y.size() - 1; ++i) {
    int j = i + 1;
    while (j < s_y.size() && pow2(s_y[j].y-s_y[i].y) <= d2_min) {
      if (pow2(s_y[j].x-s_x[mid].x) <= d2_min) {
        double tmp = dist2(s_y[j], s_y[i]);
        if (tmp < ans) {
          ans = tmp;
        }
      }
      j++;
    }
  }
  return ans;
}

int main() {
  int n;
  while (1) {
    cin >> n;
    if (n == 0) break;
    double x, y;
    vector<Point> s_x;
    vector<Point> s_y;
    while (n-- > 0) {
      cin >> x >> y;
      Point p = {x, y};
      s_x.push_back(p);
      s_y.push_back(p);
    }

    sort(s_x.begin(), s_x.end(), by_x);
    sort(s_y.begin(), s_y.end(), by_y);
    double ans = closest_pair(s_x, 0, s_x.size(), s_y);
    if (ans >= 100000000.0) {
      cout << "INFINITY" << endl;
    } else {
      cout << fixed;
      cout << setprecision(4) << sqrt(ans) << endl;
    }
  }
}
