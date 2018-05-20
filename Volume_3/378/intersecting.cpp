//
// NOTE: be careful for printing -0.00

#include <iostream> 
using namespace std;

// ax + by = c
struct Line {
    int a;
    int b;
    int c;
};

Line get_line(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        return {1, 0, x1};
    } else if (y1 == y2) {
        return {0, 1, y1};
    } else {
        return {y2-y1, x1-x2, x1*y2-x2*y1};
    }
}


void solve(int a[8]) {
    Line l1 = get_line(a[0], a[1], a[2], a[3]);
    Line l2 = get_line(a[4], a[5], a[6], a[7]);
    //cout << l1.a << "," << l1.b << "," << l1.c << endl;
    //cout << l2.a << "," << l2.b << "," << l2.c << endl;
    int delta = l1.a*l2.b - l2.a*l1.b;
    int dx = l1.c*l2.b - l2.c*l1.b;
    int dy = l1.a*l2.c - l2.a*l1.c;
    //cout << dy << endl;
    
    if (delta == 0) {
        if (dx == 0 && dy == 0) {
            cout << "LINE" << endl;
        } else {
            cout << "NONE" << endl;
        }
    } else {
        double x = dx == 0 ? 0.0 : dx*1.00 / delta;
        double y = dy == 0 ? 0.0 : dy*1.00 / delta;
        cout.precision(2);
        cout << fixed;
        cout << "POINT " << x << " " << y << endl;
    }
}

int main() {
    cout << "INTERSECTING LINES OUTPUT" << endl;
    int N;
    int a[8];
    cin >> N;
    while (N--) {
        for (int i=0;i<8;++i)
            cin >> a[i];
        solve(a);
    }
    cout << "END OF OUTPUT" << endl;    
}
