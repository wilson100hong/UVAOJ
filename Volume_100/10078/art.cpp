#include <iostream> 
#include <vector>

using namespace std;

struct Vector2 {
    int x;
    int y;
};

double cross(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

bool solve(const vector<Vector2>& pts) {
    int n = pts.size();
    bool dir;
    
    for (int i=0;i<n;++i) {
        int j = (i+1) % n;
        int k = (i+2) % n;
        Vector2 v1 = {pts[j].x-pts[i].x, pts[j].y-pts[i].y};
        Vector2 v2 = {pts[k].x-pts[j].x, pts[k].y-pts[j].y};
        bool ccw = cross(v1, v2) > 0;
        if (i == 0) {
            dir = ccw;
        } else {
            if (ccw != dir) return true;
        }
    }
    return false;
}

int main() {
    int N, x, y;
    while (cin >> N) {
        if (!N) break;
        vector<Vector2> pts;
        for (int n=0;n<N;n++) {
            cin >> x >> y;
            pts.push_back({x, y});
        }
        if (solve(pts)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

}
