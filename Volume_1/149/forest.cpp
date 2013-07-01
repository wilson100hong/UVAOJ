#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define EPS 1e-6
inline bool is_zero(float n) {
    return abs(n) < EPS;
}

struct Point{
    int x;
    int y;
};

// Cos 0.01 deg
const float fCosMax = 0.99999998476912904932780850903444f;
const float fRadToDeg = 57.295779513082320876798154814105f;

inline float dist(const Point& a, const Point& b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt((float) (dx * dx + dy * dy));
}

inline float dot(const Point& o, const Point& a, const Point& b) {
    Point va = {a.x - o.x, a.y - o.y};
    Point vb = {b.x - o.x, b.y - o.y};
    return (float) (va.x * vb.x + va.y * vb.y);
}

inline bool Hide(const int d, const Point& eye, const Point& front, const Point& back) {
    float ef = dist(eye, front);
    float eb = dist(eye, back);
    float cos_fb = dot(eye, front, back) / (ef * eb);
    if (cos_fb >= fCosMax) 
        return true;

    float angle = acos(cos_fb)  * fRadToDeg;
    float angle_front = asin(d / 2.f / ef) * fRadToDeg;
    float angle_back = asin(d / 2.f / eb) * fRadToDeg;
    return angle - angle_front - angle_back <= 0.01f;
}

vector<Point> BuildShell(int layer) {
    vector<Point> pts;
    int top = layer * 100;
    int right = top;
    int left = layer * -100 + 100;
    int bottom = left;
    // 1. Top & bottom
    Point p;
    p.y = top;
    for (int i = left; i <= right; i += 100) {
        p.x = i;
        p.y = top;
        pts.push_back(p);
        p.y = bottom;
        pts.push_back(p);
    }
    // 2. Right & left
    for (int j = bottom + 100; j <= top - 100; j += 100) {
        p.y = j;
        p.x = left;
        pts.push_back(p);
        p.x = right;
        pts.push_back(p);
    }
    return pts;
}

#define MAX_LAYER 12

int main() {
    /*
    Point eye;
    eye.x = 46; eye.y = 38;
    Point front;
    front.x = 0; front.y = 0;
    Point back;
    back.x = 200; back.y = 200;
    cout << Hide(10, eye, front, back) << endl;
    */

    float id, ix, iy;
    while (cin >> id >> ix >> iy) {
        if (is_zero(id) && is_zero(ix) && is_zero(iy))
            break;
        int d = (int) (id * 100);
        Point eye;
        eye.x = ((int) (ix * 100 + 0.5)) % 100; 
        eye.y = ((int) (iy * 100 + 0.5)) % 100;
        
        int total = 0;
        int sum = 0;
        for (int layer = 1; layer <= MAX_LAYER; ++layer) {
            vector<Point> outers = BuildShell(layer);
            for (int i = 0; i < outers.size(); ++i) {
                total++;
                Point& back = outers[i];
                bool hide = false;
                // loop for all inner trees
                for (int layer2 = 1; layer2 < layer; ++layer2) {
                    vector<Point> inners = BuildShell(layer2);  
                    for (int j = 0; j < inners.size(); ++j) {
                        Point& front = inners[j];                        
                        if (Hide(d, eye, front, back)) {
                            hide = true;
                            break;
                        }
                    }
                    if (hide) {
                        break;
                    }
                }
                if (!hide) {
                    sum++;
                }
            }
        }
        cout << sum << endl;
    }
}
