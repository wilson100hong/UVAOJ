#include <algorithm>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
using namespace std;

struct Point {
    int x;
    int y;
};

int ComparePoint(const Point& p1, const Point& p2) {
    return p1.x > p2.x;
}

double Distance(const Point& p1, const Point& p2) {
    double dx = static_cast<double>(p1.x - p2.x);
    double dy = static_cast<double>(p1.y - p2.y);
    return sqrt(dx*dx + dy*dy);
}

double Beam(const Point& p1, const Point& p2, int peak) {
    // p2.y > p1.y
    if (p2.y < p1.y) cout << "FUCK YOU" << endl;
    if (p2.y <= p1.y || p2.y <= peak) return 0.f;
    double ratio =  static_cast<double>((p2.y - peak)) / (p2.y - p1.y);
    if (ratio > 1.f) ratio = 1.f;
    return Distance(p1, p2) * ratio;
}

double Solve(vector<Point>& points) {
    sort(points.begin(), points.end(), &ComparePoint);
    double sum = 0.f;
    int peak = 0;
    bool upside = true;

    for (int i = 0; i < points.size(); ++i) {
        if (upside && i < points.size() - 1) {
            sum += Beam(points[i], points[i + 1], peak);
        }
        if (points[i].y > peak) {
            peak = points[i].y;
        }
        upside = !upside;
    }
    return sum;
}

int main() {
    cout << std::fixed;
    int round; cin >> round;
    while (round--) {
        int n; cin >> n;
        vector<Point> points;
        while (n--) {
            Point p;
            cin >> p.x >> p.y;
            points.push_back(p);
        }

        cout << std::setprecision(2) << Solve(points) << endl;
    }
}
