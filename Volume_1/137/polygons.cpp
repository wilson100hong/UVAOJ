#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

// TODO: simply with Vec2D(ps, pt)
using namespace std;
#define EPS 1e-6

bool Equals(double a, double b) {
    return abs(a - b) < EPS;
}

class Vec2D{ // represent as point or vector
public:
    Vec2D() {}
    Vec2D(double x_, double y_) : x(x_), y(y_) {}
    Vec2D(const Vec2D& ps, const Vec2D& pt) {
        x = pt.x - ps.x;
        y = pt.y - ps.y;
    }
    inline void Dump() {
      cout << "(" << x << "," << y << ")" << endl;
    }
    inline bool operator == (const Vec2D &rhs) const {
        return Equals(x, rhs.x) && Equals(y, rhs.y);
    }
    inline bool operator > (const Vec2D &rhs) const {
        return (x > rhs.x) || (Equals(x, rhs.x) && y > rhs.y);
    }
    inline bool operator < (const Vec2D &rhs) const {
        return (x < rhs.x) || (Equals(x, rhs.x) && y < rhs.y);
    }
    inline Vec2D operator+ (const Vec2D& rhs) const {
        Vec2D result;
        result.x = x + rhs.x;
        result.y = y + rhs.y;
        return result;
    }
    inline Vec2D operator- (const Vec2D& rhs) const {
        Vec2D result;
        result.x = x - rhs.x;
        result.y = y - rhs.y;
        return result;
    }
    inline double operator* (const Vec2D& rhs) const { // dot
        return x * rhs.x + y * rhs.y;
    }
    inline double operator^ (const Vec2D& rhs) const { // cross
        return x * rhs.y - y * rhs.x;
    }
    double x;
    double y;
};
typedef Vec2D Point2D;

double Cross(const Point2D& o, const Point2D& a, const Point2D& b) {
    Vec2D va(o, a);
    Vec2D vb(o, b);
    return va ^ vb;
}

// 2: overlapped in a region
// 1: intersect on one point
// 0: no intersection
// -1: invalid input
int Intersect(Point2D p1, Point2D p2, Point2D p3, Point2D p4, Point2D& intr) {
    if (p1 == p2 || p3 == p4) {
        // Make sure inputs are valid segments
        return -1;
    }
    // At this point, p1 != p2  and p3 != p4
    // Frce p1 < p2 and p3 < p4
    if (p2 < p1) swap(p1, p2);
    if (p4 < p3) swap(p3, p4);
    
    // Complete overlapped
    if (p1 == p3 && p2 == p4){
        intr = p1;
        return 2;
    }
    
    Vec2D v1(p2.x - p1.x, p2.y - p1.y);
    Vec2D v2(p4.x - p3.x, p4.y - p3.y);
    double cross = v1 ^ v2;
    // Share start or end
    if (p1 == p3 || p2 == p4) {
        intr = (p1 == p3) ? p1 : p2;
        return Equals(cross, 0) ? 2 : 1;
    }
    // Head to or from tail
    if (p1 == p4 || p2 == p3) {
        intr = (p1 == p4) ? p1 : p2;
        return 1;
    }
    
    // Force p1 < p3: v1.start < v2.start
    if (p1 > p3) {
        swap(p1, p3);
        swap(p2, p4);
        swap(v1, v2);
        cross = v1 ^ v2;
    }
    
    // If two segments are parallel
    if (Equals(v1 ^ v2, 0)) {
        Vec2D vs(p3.x - p1.x, p3.y - p1.y);
        // Common line
        if (Equals(vs ^ v2, 0)) {
            // Overlap:   (p1 [p3 p2) p4]
            if (p2 > p3) {
                intr = p3;
                return 2;
            }
        }
        // Not common line nor overlap has no intersection
        return 0;
    }
    
    // Not parallel
    // Rectangle test for performance
    double miny1 = p1.y, maxy1 = p2.y, miny2 = p3.y, maxy2 = p4.y;
    if (miny1 > maxy1) swap(miny1, maxy1);
    if (miny2 > maxy2) swap(miny2, maxy2);
    // Rectangle not cross
    if (p1.x > p4.x || p3.x > p2.x || miny1 > maxy2 || miny2 > maxy1)
        return 0;
    
    // Cross test
    Vec2D vs1(p1.x - p3.x, p1.y - p3.y);
    Vec2D vs2(p2.x - p3.x, p2.y - p3.y);
    Vec2D vt1(p3.x - p1.x, p3.y - p1.y);
    Vec2D vt2(p4.x - p1.x, p4.y - p1.y);
    double cs1v2, cs2v2, ct1v1, ct2v1;
    // One point is on the other's segment
    if (Equals(cs1v2 = vs1 ^ v2, 0) && p4 > p1 && p1 > p3) {
        intr = p1;  return 1;
    }
    if (Equals(cs2v2 = vs2 ^ v2, 0) && p4 > p2 && p2 > p3) {
        intr = p2;  return 1;
    }
    if (Equals(ct1v1 = vt1 ^ v1, 0) && p2 > p3 && p3 > p1) {
        intr = p3;  return 1;
    }
    if (Equals(ct2v1 = vt2 ^ v1, 0) && p2 > p4 && p3 > p1) {
        intr = p4;  return 1;
    }
    //  Not intersect
    if (cs1v2 * cs2v2 > 0 || ct1v1 * ct2v1 > 0)  return 0;
    
    // Intersect, calculate the point
    double ConA = p1.x * v1.y - p1.y * v1.x;
    double ConB = p3.x * v2.y - p3.y * v2.x;
    intr.x = (ConB * v1.x - ConA * v2.x) / cross;
    intr.y = (ConB * v1.y - ConA * v2.y) / cross;
    return 1;
}


class ConvexHull{
public:
    ConvexHull() {}
    ConvexHull(vector<Point2D> pts_) {
        // Convex hull algorithm
        sort(pts_.begin(), pts_.end());
        
        int n = pts_.size();
        pts = vector<Point2D>(2 * n);
        int k = 0;
        for (int i = 0; i < n; ++i) {
            while (k >= 2 && Cross(pts[k-2], pts[k-1], pts_[i]) <= 0)  k--;
            pts[k++] = pts_[i];
        }
        for (int i = n - 2, t = k + 1; i >= 0; --i) {
            while (k >= t && Cross(pts[k-2], pts[k-1], pts_[i]) <= 0) k--;
            pts[k++] = pts_[i];
        }
        pts.resize(k);
    }
    void Dump() {
        for (int i = 0; i < pts.size(); ++i)
            cout << pts[i].x << ", " << pts[i].y << endl;
        cout << endl;
    }
    bool Contains(const Point2D& p) {
       double expect_area = Area();
       double sum = 0;
       int n = pts.size() - 1;
       for (int i = 0; i < n; ++i)
          sum += TriangleArea(p, pts[i], pts[i+1]);
       return Equals(sum, expect_area);
    }
    double TriangleArea(const Point2D& o, const Point2D& a, const Point2D& b) {
       vector<Point2D> vertices;
       vertices.push_back(o);
       vertices.push_back(a);
       vertices.push_back(b);
       vertices.push_back(o);
       return Area(vertices);
    }
    double Area(vector<Point2D>& vertices) {
       int n = vertices.size() - 1;
       double area = 0;
       for (int i = 0; i < n; ++i)
          area += (vertices[i].x * vertices[i+1].y - vertices[i].y * vertices[i+1].x);
       return 0.5 * abs(area);
    }
    double Area() {    return Area(pts);}
   
    vector<Point2D> Contains(ConvexHull& other) {
       vector<Point2D> sets;
       Point2D intr;
       for (int i = 0;i < other.pts.size() - 1; ++i) {
          if (Contains(other.pts[i])) {
             sets.push_back(other.pts[i]);
            // cout << "contain! ";
            // other.pts[i].Dump();
          }
          for (int j = 0; j < pts.size() - 1; ++j) {
             if (Intersect(other.pts[i], other.pts[i+1],
                  pts[j], pts[j+1], intr)) {
                sets.push_back(intr);
             //   cout << "intersect! " << i << ", " << j << endl;
             //   intr.Dump();
             }
          }
       }
       return sets;
    }
    vector<Point2D> pts;
};

vector<Point2D> Intersect(ConvexHull& ch1, ConvexHull& ch2) {
   vector<Point2D> sets = ch1.Contains(ch2);
   vector<Point2D> another_sets = ch2.Contains(ch1);
   sets.insert(sets.end(), another_sets.begin(), another_sets.end());
   return sets;
}

int main() {
   int n1, n2;
   vector<Point2D> poly1;
   vector<Point2D> poly2;
   Point2D p;
   while (cin >> n1) {
      if (n1 == 0) break;
      for (int i = 0; i < n1; ++i) {
         cin >> p.x >> p.y;
         poly1.push_back(p);
      }
      cin >> n2;
      for (int i = 0; i < n2; ++i) {
         cin >> p.x >> p.y;
         poly2.push_back(p);
      }
      ConvexHull ch1(poly1);
      ConvexHull ch2(poly2);
      //ch1.Dump();
      //ch2.Dump();
      double area1 = ch1.Area();
      double area2 = ch2.Area();
      //cout << area1 << endl << area2 << endl;
      vector<Point2D> inter_poly = Intersect(ch1, ch2);
      ConvexHull ch_inter(inter_poly);
      //ch_inter.Dump();
      double area_inter = ch_inter.Area();
      // TODO: formatting
      double total = area1 + area2 - 2 * area_inter;
      printf("%8.2f", total);

      poly1.clear();
      poly2.clear();
   }
   cout << endl;
}
