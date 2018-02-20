// 2018/02/14
// Minimal Enclosing Circle:
// https://www.cse.buffalo.edu//~jinhui/courses/cse581/slides/slides4b.pdf
//
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>

using namespace std;
#define EPS 1e-6

bool equals(double a, double b) {
    return abs(a-b) < EPS;
}

// Vec2 can be used for point and 2D vector
class Vec2{
public:
    Vec2() {}
    Vec2(double _x, double _y) : x(_x), y(_y) {}

    inline bool operator == (const Vec2& rhs) const {
        return equals(x, rhs.x) && equals(y, rhs.y);
    }

    inline Vec2 operator+ (const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    inline Vec2 operator- (const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    inline Vec2 operator/ (double f) const {
        return Vec2(x/f, y/f);
    }
    
    inline Vec2 operator* (double f) const {
        return Vec2(x*f, y*f);
    }

    double x;
    double y;
};

double len2(const Vec2& p) {
    return p.x*p.x + p.y*p.y;  // also use Vec2 as vector2D
}

bool outside(const Vec2& p, const Vec2& c, double r2) {
    return len2(p - c) > r2;
}

double cross(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

pair<Vec2, double> circle(const Vec2& p1, const Vec2& p2) {
    return make_pair((p1+p2)/2, len2(p1-p2)/4.0);
}

pair<Vec2, double> circle(const Vec2& p1, const Vec2& p2, const Vec2& p3) {
    Vec2 c;
    double r2;
    // vector perpendicular to p1-p2
    Vec2 va = Vec2(p1.y-p2.y, p2.x-p1.x);
    // vector perpendicular to p1-p3
    Vec2 vb = Vec2(p1.y-p3.y, p3.x-p1.x);
    if (equals(cross(va, vb), 0.0)) {
        Vec2 tc;
        double tr2;
        tie(c, r2) = circle(p1, p2);
        tie(tc, tr2) = circle(p1, p3);
        if (tr2 > r2) {
            c = tc;
            r2 = tr2;
        }
        tie(tc, tr2) = circle(p2, p3);
        if (tr2 > r2) {
            c = tc;
            r2 = tr2;
        }
        return make_pair(c, r2);
    }
    // center between p1-p2
    Vec2 pa = (p1 + p2) / 2; 
    // center between p1-p3
    Vec2 pb = (p1 + p3) / 2;

    double delta = va.x*vb.y - va.y*vb.x;
    double t = ((pb.x-pa.x)*vb.y - (pb.y-pa.y)*vb.x) / delta;
    c = pa + va*t;
    r2 = len2(c-p1);
    return make_pair(c, r2);
}

// return center and radius^2 of MEC
pair<Vec2, double> MEC(const vector<Vec2>& pts) {
    
    Vec2 c;
    double r2 = 0.0;
    for (int i=0;i<pts.size();++i) {
        if (outside(pts[i], c, r2)) {
            c = pts[i];
            r2 = 0.0;
            for (int j=0;j<i;++j) {
                if (outside(pts[j], c, r2)) {
                    // pi and pj must be on boundary
                    tie(c, r2) = circle(pts[i], pts[j]);
                    for (int k=0;k<j;++k) {
                        if (outside(pts[k], c, r2)) {
                            tie(c, r2) = circle(pts[i], pts[j], pts[k]);
                        }
                    }
                }
            }
        }
    }
    return make_pair(c, r2);
}

int main() {
    int n;
    while (cin >> n) {
        if (n==0) break;
        vector<Vec2> pts;
        while (n--) {
            int x,y;
            cin >> x;
            cin >> y;
            pts.push_back(Vec2(x, y));
        }
    
        Vec2 c;
        double r2;
        random_shuffle(pts.begin(), pts.end());
        tie(c, r2) = MEC(pts);

        double R, R2;
        cin >> R;
        R2 = R*R;

        if (r2 > R2) {
            cout << "There is no way of packing that polygon." << endl;
        } else {
            cout << "The polygon can be packed in the circle." << endl;
        }
   }
}
