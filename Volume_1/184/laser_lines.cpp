#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
  if (a < b)
    return gcd(b, a);
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

int abs(int a) {
  return a > 0 ? a : -a;
}

void Factorize(int& a, int& b) {
  if (a == 0 && b == 0) 
    return;
  
  int g = gcd(abs(a), abs(b));
  a /= g;
  b /= g;
}

struct Point{
  int x;
  int y;
};

bool ComparePoint(const Point& p1, const Point& p2) {
  if (p1.x == p2.x)
    return p1.y < p2.y;
  else
    return p1.x < p2.x;
}

struct PointComp {
  bool operator() (const Point& p1, const Point& p2) {
    return ComparePoint(p1, p2);
  }
};

void DumpPoint(const Point& p) {
  cout << "(";
  cout.width(4);
  cout << p.x << ",";
  cout.width(4);
  cout << p.y << ")";
}

struct Line {
  Point slope;
  double intercept_y_then_x;
  Point src;
  Point dst;
};

bool CompareLine(const Line& l1, const Line& l2) {
  if (l1.slope.x == l2.slope.x) {
    if (l1.slope.y == l2.slope.y) 
      return l1.intercept_y_then_x < l2.intercept_y_then_x;
    else
      return l1.slope.y < l2.slope.y;
  } else {
    return l1.slope.x < l2.slope.x;
  }
}

typedef set<Point, PointComp> PointSet;

void DumpPointSet(const PointSet& p_set) {
  PointSet::iterator it;
  for (it = p_set.begin(); it != p_set.end(); ++it) {
    DumpPoint(*it);
  }
  cout << endl;
}

bool ComparePointSet(const PointSet& ps1, const PointSet& ps2) {
  PointSet::iterator it1;
  PointSet::iterator it2;
  for (it1 = ps1.begin(), it2 = ps2.begin();
       it1 != ps1.end() && it2 != ps2.end();
       ++it1, ++it2) {
    if (it1->x == it2->x && it1->y == it2->y)
      continue;
    return ComparePoint(*it1, *it2);
  }
  return true; 
}

#define EPS 1e-6
bool CommonLine(const Line& l1, const Line& l2) {
  return l1.slope.x == l2.slope.x &&
         l1.slope.y == l2.slope.y &&
         fabs(l1.intercept_y_then_x - l2.intercept_y_then_x) < EPS;       
}

void Solve(vector<Point>& points) {
  // Sort points
  sort(points.begin(), points.end(), ComparePoint);
  Line line;
  vector<Line> lines;
  // Compute all Lines
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i + 1; j < points.size(); ++j) {
      // TODO(wilsonhong): not consider equal points now
      Point p1 = points[i], p2 = points[j];
      line.src = p1; line.dst = p2;
      // p1 < p2
      int dx = p2.x - p1.x, dy = p2.y - p1.y;
      if (dx != 0) // intercept on y
        line.intercept_y_then_x = ((double) (p2.x*p1.y - p1.x*p2.y)) / dx;
      else   // intercept on x
        line.intercept_y_then_x = (double) p1.x;
      Factorize(dx, dy);
      line.slope.x = dx; line.slope.y = dy;
      lines.push_back(line);   
    }
  }

  // Sort lines 
  sort(lines.begin(), lines.end(), CompareLine);
  
  // Group points
  vector<PointSet> point_set_groups;
  int cur = 0;
  PointSet point_set;
  bool line_found = false;
  while (cur < lines.size()) {
    point_set.insert(lines[cur].src);
    point_set.insert(lines[cur].dst);
    int next = cur + 1;
    while (next < lines.size() && CommonLine(lines[cur], lines[next])) {
      point_set.insert(lines[next].src);
      point_set.insert(lines[next].dst);
      next++;
    }
    if (point_set.size() > 2) 
      point_set_groups.push_back(point_set);
    point_set.clear();
    cur = next;
  }

  if (point_set_groups.size() > 0) {
    cout << "The following lines were found:" << endl;
    sort(point_set_groups.begin(), point_set_groups.end(), ComparePointSet);
    for (int i = 0; i < point_set_groups.size(); ++i) 
      DumpPointSet(point_set_groups[i]);
  } else
    cout << "No lines were found" << endl;
}

int main() {
  vector<Point> points;
  Point p;
  while(cin >> p.x >> p.y) {
    if (p.x == 0 && p.y == 0) {
      if (points.size() > 0) {
        Solve(points);
      }
      points.clear();
    } else {
      points.push_back(p);
    }
  }
}
