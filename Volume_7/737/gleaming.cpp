#include <iostream>
#include <algorithm>   // std::max, std::min
using namespace std;

typedef long long int ll;
struct Segment {
    ll a;
    ll b;
};

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        Segment sx, sy, sz;
        bool zero = false;
        for (int i=0;i<N;++i) {
            ll x, y, z, d;
            cin >> x >> y >> z >> d;
            if (zero) continue;
            if (i == 0) {
                sx = {x, x+d};
                sy = {y, y+d};
                sz = {z, z+d};
            } else {
                sx = { max(sx.a, x), min(sx.b, x+d) };
                sy = { max(sy.a, y), min(sy.b, y+d) };
                sz = { max(sz.a, z), min(sz.b, z+d) };
                if (sx.a >= sx.b || sy.a >= sy.b || sz.a >= sz.b) {
                    zero = true;
                }
            }
        }
        if (zero) {
            cout << 0 << endl;
        } else {
            cout << (sx.b-sx.a) * (sy.b-sy.a) * (sz.b-sz.a) << endl;
        }
    }
}
