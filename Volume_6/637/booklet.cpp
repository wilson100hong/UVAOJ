#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool blank(int x, int pages) {
    return !(0 < x && x <= pages);
}

string i2s(int x, bool blank) {
    if (blank) return "Blank";
    return to_string(x);
}

void solve(int pages) {
    cout << "Printing order for " << pages << " pages:" << endl;
    int sheets = (pages+3)/4;
    int n = sheets * 4;
    // front left, front right, back left, back right
    int fl = n, fr = 1, bl = 2, br = n-1;
    for (int i=0;i<sheets;++i) {
        int fl = n-2*i, fr = 1+2*i, bl = 2*(i+1), br = n-2*i-1;
        bool blank_fl = blank(fl, pages);
        bool blank_fr = blank(fr, pages);
        if (!blank_fl || !blank_fr) {
            cout << "Sheet " << i+1 
                 << ", front: " << i2s(fl, blank_fl) 
                 << ", " << i2s(fr, blank_fr) << endl;
        }

        bool blank_bl = blank(bl, pages);
        bool blank_br = blank(br, pages);
        if (!blank_bl || !blank_br) {
            cout << "Sheet " << i+1 
                 << ", back : " << i2s(bl, blank_bl) 
                 << ", " << i2s(br, blank_br) << endl;
        }
    }
}


int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        solve(n);
    }
}
