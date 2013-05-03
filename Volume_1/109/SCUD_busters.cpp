#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

struct Point{
  int x;
  int y;
};

// < 0: CW
// ==0: common line
// > 0: CCW
double Cross(const Point& o, const Point& a, const Point& b) {
  return (a.x - o.x)*(b.y - o.y) - (a.y -o.y)*(b.x - o.x);
}

bool CompareX(const Point& a, const Point& b) {
  return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

bool NotCCW(const vector<Point>& points, const Point& p) {
  int m = points.size();
  return Cross(points[m - 2], points[m - 1], p) <= 0;
}

void AMC_ConvexHull(const vector<Point>& points, vector<Point>& hull) {
  vector<Point> uppers;
  vector<Point> lowers;
  // Lower part
  for (int i=0;i<points.size();++i) {
    while (lowers.size() >=2 && NotCCW(lowers, points[i])) 
      lowers.pop_back(); 
    lowers.push_back(points[i]);
  }
  // Upper part
  for (int i=points.size()-1;i>=0;--i) {
    while (uppers.size() >=2 && NotCCW(uppers, points[i])) 
      uppers.pop_back(); 
    uppers.push_back(points[i]);
  }

  for (int i=0;i<lowers.size()-1;++i)
    hull.push_back(lowers[i]);
  for (int i=0;i<uppers.size()-1;++i)
    hull.push_back(uppers[i]);
}

void DumpConvexHull(const vector<Point>& hull) {
  cout << "Hull:" << endl;
  for (int i=0; i<hull.size(); ++i) 
    cout << hull[i].x << " " << hull[i].y << endl;
}

int ConvexHullArea2X(vector<Point>& hull) {
  int n = hull.size();
  Point p = hull[0];
  hull.push_back(p);
  int area_2x = 0;
  for (int i=1;i<=n;++i) 
    area_2x += (hull[i-1].x*hull[i].y - hull[i-1].y*hull[i].x);
  hull.pop_back();
  return area_2x;
}

int TriangleArea2X(const Point& a, const Point& b, const Point& c) {
  return abs(Cross(a, b, c));  
}

bool InConvexHull(vector<Point>& hull, int area_2x, const Point& p) {
  int n = hull.size();
  Point tp = hull[0];
  hull.push_back(tp);

  int sum_2x = 0;
  for (int i=0; i<n; ++i) 
    sum_2x += TriangleArea2X(p, hull[i], hull[i+1]);

  hull.pop_back();
  return sum_2x == area_2x;

}

int main() {
  int N;
  vector<Point> sites;
  vector<vector<Point> > kingdoms;
  vector<int> area_2xs;

  // build convex hull for all kingdoms
  while (cin >> N) {
    if (N == -1)
      break;
    while (N-- > 0) {
      Point p;
      cin >> p.x >> p.y;
      sites.push_back(p);
    }
    sort(sites.begin(), sites.end(), CompareX);
    vector<Point> kingdom;
    AMC_ConvexHull(sites, kingdom);

    //DumpConvexHull(kingdom); // TEST; 
    area_2xs.push_back(ConvexHullArea2X(kingdom));
    kingdoms.push_back(kingdom);
    sites.clear();
  }
  
  // read all missiles
  vector<Point> missles;
  Point missle;
  while (cin >> missle.x >> missle.y) 
    missles.push_back(missle);
  
  int total_area_2x = 0.f;
  for (int i=0;i<kingdoms.size();++i) {
    for (int j=0;j<missles.size();++j) {
      if (InConvexHull(kingdoms[i], area_2xs[i], missles[j])) {
        total_area_2x += area_2xs[i];
        break;
      }
    }
  }
  
  cout << total_area_2x / 2 << ".";
  if (total_area_2x % 2 == 0)
    cout << "00";
  else 
    cout << "50";
  cout << endl;
}
