#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <limits>
using namespace std;

struct Point{
    double x;
    double y;
};

struct Vector{
    double x;
    double y;
};

struct Segment{
    Point p1;
    Point p2;
};

double len(Point a, Point b) {
    double dx = b.x - a.x, dy = b.y - a.y;
    if (dx == .0 && dy == .0) return .0;
    return sqrt(dx*dx + dy*dy);
}

double len(const Segment& s) {
    return len(s.p1, s.p2); 
}

double len(const Vector& v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

double cross(Point o, Point a, Point b) {
    // cross product of oa and ob.
    double oax = a.x - o.x, oay = a.y - o.y;
    double obx = b.x - o.x, oby = b.y - o.y;

    return oax*oby - oay*obx;
}

double dot(const Vector& v1, const Vector& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

Point proj(const Point& p, const Segment& s) {
    // assume projection point falls into segment 
    Point p1 = s.p1, p2 = s.p2;
    double dx = p2.x-p1.x, dy = p2.y-p1.y;
    double t = (dx*(p.x-p1.x) + dy*(p.y-p1.y)) / (dx*dx + dy*dy);
    double nx = p1.x + t*dx, ny = p1.y + t*dy;
    return {nx, ny};
}

// distance from m to line ra-rb
pair<double, Point> dist(Segment s, Point p) {
    // make sure s.p1 != s.p2
    double ls = len(s);
    if (len(s) == 0.0) return make_pair(len(s.p1, p), s.p1);
    
    Vector v = {s.p2.x - s.p1.x, s.p2.y - s.p1.y};
    Vector v1 = {p.x - s.p1.x, p.y - s.p1.y};
    Vector v2 = {p.x - s.p2.x, p.y - s.p2.y};

    if (dot(v, v1) <= 0) return make_pair(len(v1), s.p1);
    if (dot(v, v2) >= 0) return make_pair(len(v2), s.p2);

    double cr = cross(s.p1, s.p2, p);
    double d = abs(cr/ls);

    return make_pair(d, proj(p, s));
}

int main() {
    Point p, p1, p2;
    
    while (cin >> p.x) {
        cin >> p.y;

        int N;
        cin >> N;

        cin >> p1.x >> p1.y;
        double shortest = numeric_limits<double>::max();
        Point station;
        for (int i=0;i<N;++i) {
            cin >> p2.x >> p2.y;
            auto ret = dist({p1, p2}, p);
            if (ret.first < shortest) {
                station = ret.second;
                shortest= ret.first;
            }
            p1 = p2;
        }

        cout.precision(4);
        cout << fixed << station.x << endl;
        cout << fixed << station.y << endl;

    }
}
