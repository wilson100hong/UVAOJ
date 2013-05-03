#include <iostream>
#include <cmath>
using namespace std;

#define EPS 1e-8

class Point{
public:
  double x;
  double y;
  Point(double x_, double y_) {
    x = x_; y = y_;
  }
};

double cross(const Point& o, const Point& a, const Point& b) {
  return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

bool common_line(const Point& p1, const Point& p2, const Point& p3) {
  return fabs(cross(p1, p2, p3)) < EPS;
}

bool intersect_common_line(const Point& p1, const Point& p2, const Point& p) {
  return common_line(p1, p2, p) 
     && p.x >= min(p1.x, p2.x)
     && p.x <= max(p1.x, p2.x)
     && p.y >= min(p1.y, p2.y)
     && p.y <= max(p1.y, p2.y);
}

bool intersec_segments(
    const Point& a1, const Point& a2, 
    const Point& b1, const Point& b2) {
  double c1 = cross(a1, a2, b1);
  double c2 = cross(a1, a2, b2);
  double d1 = cross(b1, b2, a1);
  double d2 = cross(b1, b2, a2);
 
  if (c1 * c2 < 0 && d1 * d2 < 0) return true;
  if (intersect_common_line(a1, a2, b1)) return true;
  if (intersect_common_line(a1, a2, b2)) return true;
  if (intersect_common_line(b1, b2, a1)) return true;
  if (intersect_common_line(b1, b2, a2)) return true;
  return false;
}

bool in_region(const Point& topleft, const Point& bottomright, const Point& p) {
  return topleft.x <= p.x && p.x <= bottomright.x 
      && bottomright.y <= p.y && p.y <= topleft.y;
}

int main() {

  
  int n;
  cin >> n;
  
  while (n-- > 0) {
    int lsx, lsy, lex, ley;
    cin >> lsx >> lsy >> lex >> ley; 
    Point line1(lsx, lsy);
    Point line2(lex, ley);
    int rrlx, rrty, rrrx, rrby;
    cin >> rrlx >> rrty >> rrrx >> rrby;
    
    int rlx = min(rrlx, rrrx);
    int rrx = max(rrlx, rrrx);
    int rty = max(rrty, rrby);
    int rby = min(rrty, rrby);
    bool inter = 
        intersec_segments(line1, line2, Point(rlx, rty), Point(rrx, rty))
        || intersec_segments(line1, line2, Point(rlx, rby), Point(rrx, rby))
        || intersec_segments(line1, line2, Point(rlx, rty), Point(rlx, rby))
        || intersec_segments(line1, line2, Point(rrx, rty), Point(rrx, rby))
        || (in_region(Point(rlx, rty), Point(rrx, rby), line1) && 
            in_region(Point(rlx, rty), Point(rrx, rby), line2));

    cout << (inter ? "T" : "F") << endl;
  }
  
}
