#include <iostream>
#include <vector>
using namespace std;
struct Point{
  int x;
  int y;
};

bool eq(const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool on_edge(const Point& p, const Point& s1, const Point& s2) {
  // since all edge are either horizontal or vertical
  return (p.x == s1.x && p.x == s2.x && (p.x < s1.x) != (p.x < s2.x)) ||
    (p.y == s1.y && p.y == s2.y && (p.y < s1.y) != (p.y < s2.y));
}

int main() {
  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;

    vector<Point> pts;
    int x, y;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      pts.push_back({x, y});
    }
    cin >> x >> y;
    Point p = {x, y};

    // test if p on polygon
    bool on_polygon = false;
    int start = -1;
    for (int i = 0, j = n - 1; i < n; j = i++) {
      if (eq(p, pts[i]) || eq(p, pts[j]) ||
          on_edge(p, pts[i], pts[j])) {
        on_polygon = true;
        break;
      }
      if (start == -1 && pts[i].y != p.y) {
        // find start point with different y-axis to p 
        start = i;
      }
    }
    if (on_polygon) {
      cout << "F" << endl;
      continue;
    }

    bool out = true;
    int from_i_y = p.y;
    
    for (int cnt = 0, i = start; cnt < n; i = (i + 1) % n, cnt++) {
      int j = (i + 1) % n;
      if (pts[i].x == pts[j].x) {  // vertical
        if (pts[i].x >= p.x) {  // on the right plane
          int k = (pts[i].y - p.y)*(pts[j].y - p.y);
          if (k > 0) {
            ;  // not intersect
          } else if (k < 0) {
            out = !out;  // normal intersect
          } else {  // k == 0
            if (pts[i].y == p.y) {  // escape from p.y
              if ((from_i_y - p.y)*(pts[j].y - p.y) < 0) {
                out = !out;  // interset
              } else {
                ;  // no-intersect
              }
            } else {  // inject into p.y
              from_i_y = pts[i].y;
            }
          }
        }
      } else { // pts[i].y == pts[j].y, horizontal
        ;  // no op  
      }
    }
    cout << (out ? "F" : "T" ) << endl;
  }
}
