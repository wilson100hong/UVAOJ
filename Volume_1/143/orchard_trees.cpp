#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point{
  long double x;
  long double y;
};

struct Segment{
  Point p1;
  Point p2;
};

#define EPS 1e-9
inline bool isEqual(long double x, long double y) {
  return fabs(x - y) <= EPS;
}

#define UNDEF 99999.f
// Return UNDEF if not intersect or seg is horizontal
long double IntersectOnX(const Segment& seg, long double y) {
  long double x1 = seg.p1.x;
  long double y1 = seg.p1.y;
  long double x2 = seg.p2.x;
  long double y2 = seg.p2.y;
  if (y1 == y2) // Horizontal 
    return UNDEF;
  if (min(y1, y2) <= y  && y <= max(y1, y2)) {
    if (x1 == x2)
      return x1;
    return x1 + (x2 - x1) * (( y - y1 ) / ( y2 - y1)) ;
  } else {
    return UNDEF;
  }
}

int main() {
  long double px, py;
  Point pts[3];
  Segment segs[3]; 
  vector<long double> inters;  // Intersects
  while (1) {
    for (int i = 0; i < 3;++i) 
      cin >> pts[i].x >> pts[i].y;
    
    if (pts[0].x == 0 && pts[0].y == 0 &&
        pts[1].x == 0 && pts[1].y == 0 &&
        pts[2].x == 0 && pts[2].y == 0)
      break;
    
    // Build segments
    segs[0].p1 = pts[0];
    segs[0].p2 = pts[1];
    segs[1].p1 = pts[1];
    segs[1].p2 = pts[2];
    segs[2].p1 = pts[2];
    segs[2].p2 = pts[0];

    int sum = 0;

    for (int y = 1; y <= 99; ++y) {
      inters.clear();
      for (int i = 0; i < 3; ++i) {
        long double i_x = IntersectOnX(segs[i], y);
        if ( !isEqual(i_x, UNDEF)) 
          inters.push_back(i_x);
      }
      if (inters.size() > 1) {
        sort(inters.begin(), inters.end());
        int left = ceil(inters[0] - EPS);
        int right = floor(inters[inters.size() - 1] + EPS);
        left = max(1, left);
        right = min(99, right);
        if (right >= left)
          sum += (right - left + 1);
      }
    }
    cout.width(4);
    cout << sum << endl;
  }
}
