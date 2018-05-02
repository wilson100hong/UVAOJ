#include <iostream>
#include <vector>
using namespace std;

struct Pt {
    int x;
    int y;
};

double area(const vector<Pt> pts) {
    int n = pts.size();
    double sum = 0.0;
    for (int i=1;i<n;++i) {
        int height = -(pts[i].y + pts[i-1].y);
        int base = pts[i].x - pts[i-1].x;
        sum += static_cast<double>(base*height)/ 2.0;
    }
    return sum;
}

void solve(const vector<Pt> pts, int w, double initial, double spent, double falling) {
    double a = area(pts);
    double cap = a * w;
    
    double water = cap * initial / 100.0;
    water -= spent;
    if (water < 0.0) {
        cout << "Lack of water. ";
        water = 0.0;
    }
    water += falling;
    if (water > cap) {
        cout << "Excess of water. ";
        water = cap;
    }
    int percentage = static_cast<int>(water*100 / cap);
    cout << "Final percentage: " << percentage << "%" << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<Pt> pts;
        while (N--) {
            int x, y;
            cin >> x >> y;
            pts.push_back({x, y});
        }
        int W;
        cin >> W;
        double initial, spent, falling;
        cin >> initial >> spent >> falling;
        
        solve(pts, W, initial, spent, falling);
    }
}
