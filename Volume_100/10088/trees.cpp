// Trap:
// (x, y) needs to be long long because of cross product could cause overflow.

#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
struct Pt{
    LL x;
    LL y;
};


LL gcd(LL a, LL b) {
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

LL solve(const vector<Pt>& pts) {
    // calculate area
    LL area2 = 0;  // area*2
    LL boundary = 0;  // point on boundary
    for (int i=0;i<pts.size();++i) {
        int j = (i+1) % pts.size();
        area2 += (pts[i].x * pts[j].y - pts[i].y * pts[j].x);
        LL dx = abs(pts[j].x - pts[i].x);
        LL dy = abs(pts[j].y - pts[i].y);
        boundary += gcd(dx, dy);
    }
    area2 = abs(area2);

    // Pick's theorem
    LL inner = (area2 - boundary + 2) / 2;
    return inner >=0 ? inner : 0;
}


int main() {
    int N;
    while (1) {
        cin >> N;
        if (!N)  break;
        vector<Pt> pts;
        for (int n=0;n<N;++n) {
            LL x, y;
            cin >> x >> y;
            pts.push_back({x, y});
        }
        cout << solve(pts) << endl;
    }
}   
