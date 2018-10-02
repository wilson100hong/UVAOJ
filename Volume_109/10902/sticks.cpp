#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Point {
    double x;
    double y;
};
struct Segment {
    Point a;
    Point b;
};

string join(const set<int>& s, const string& delimit) {
    string res = "";
    bool first = true;
    for (int x : s) {
        if (first) { 
            first = false;
        } else {
            res += delimit;
        }
        res += to_string(x+1);
    }
    return res; 
}


bool intersect1d(double a1, double a2, double b1, double b2) {
    if (a1 > a2) swap(a1, a2);
    if (b1 > b2) swap(b1, b2);
    return max(a1, b1) <= min(a2, b2);
}

double cross(const Point& o, const Point& a, const Point& b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

bool intersect(const Segment& s1, const Segment& s2) {
    return intersect1d(s1.a.x, s1.b.x, s2.a.x, s2.b.x)
        && intersect1d(s1.a.y, s1.b.y, s2.a.y, s2.b.y)
        && cross(s1.a, s1.b, s2.a) * cross(s1.a, s1.b, s2.b) <= 0
        && cross(s2.a, s2.b, s1.a) * cross(s2.a, s2.b, s1.b) <= 0;
}

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        vector<Segment> segments;
        set<int> tops;
        for (int i=0;i<N;++i) {
            Segment seg;
            cin >> seg.a.x >> seg.a.y >> seg.b.x >> seg.b.y;
            segments.push_back(seg);

            auto below = set<int>();
            for (int index : tops) {
                if (intersect(seg, segments[index])) {
                    below.insert(index);
                }
            }
            for (int b : below) {
                tops.erase(b);
            }
            tops.insert(i);
        }

        cout << "Top sticks: " << join(tops, ", ") << "." << endl; 
    }
}
