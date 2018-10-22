#include <iostream>
using namespace std;

#define MAX_P 20000

int min(int a, int b) {
    return a < b ? a : b;
}


int main() {
    int N, B, H, W;
    while (cin >> N >> B >> H >> W) {
        int best_p = MAX_P;
        int p;
        for (int i=0;i<H;++i) {
            cin >> p;
            int w;
            for (int j=0;j<W;++j) {
                cin >> w;
                if (w >= N) {
                    best_p = min(best_p, p);
                }
            }
        }
        if (best_p == MAX_P || best_p * N > B) { 
            cout << "stay home" << endl;
        } else {
            cout << N * best_p << endl;
        }
    }
}
