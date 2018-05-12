#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

struct Vector2D {
    int x;
    int y;
};

int area2(const vector<Vector2D>& pts) {
    int sum = 0;
    for (int i=0;i<pts.size();++i) {
        int j = (i+1) % pts.size();
        sum += (pts[i].x * pts[j].y - pts[j].x * pts[i].y);
    }
    return abs(sum);
}

bool compare_point(const Vector2D& p1, const Vector2D& p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

double cross(const Vector2D& o, const Vector2D& a, const Vector2D& b) {
    Vector2D v1 = {a.x - o.x, a.y - o.y};
    Vector2D v2 = {b.x - o.x, b.y - o.y};
    return static_cast<double>(v1.x*v2.y - v2.x*v1.y);
}

vector<Vector2D> convexhull(const vector<Vector2D>& input) {
    int n = input.size();
    vector<Vector2D> pts(input);
    // 1. sort on x
    sort(pts.begin(), pts.end(), compare_point);
    vector<Vector2D> res(2*n);
    int k=0;  // how many points in res

    for (int i=0;i<n;++i) {
        while (k >= 2 && cross(res[k-2], res[k-1], pts[i]) >= 0) {
            k--;
        }
        res[k++] = pts[i];
    }
    int m = k;

    for (int i=n-2;i>=0;--i) {  // skip the rightmost point since it has been added
        while (k >= m+1 && cross(res[k-2], res[k-1], pts[i]) >= 0) {
            k--;
        }
        res[k++] = pts[i];
    }

    res.resize(k-1);  // last point suppose to be euqal to the first point
    return res;
}

int main() {
    int N;
    int round = 0;
    vector<Vector2D> pts;
    while (cin >> N) {
        if (N == 0) break;

        pts.clear();

        for (int i=0;i<N;++i) {
            Vector2D p;
            cin >> p.x >> p.y;
            pts.push_back(p);
        }
        cout << "Tile #" << ++round << endl;
        int tile2 = area2(pts);
        vector<Vector2D> ch = convexhull(pts);
        int box2 = area2(ch);
        double waste = (1.0 - static_cast<double>(tile2)/box2) * 100;
        cout.precision(2);
        cout << fixed;
        cout << "Wasted Space = " << waste << " %" << endl;
        cout << endl;
        
    } 
}
