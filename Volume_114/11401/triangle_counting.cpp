#include <iostream>
#include <vector>
using namespace std;

// 2016/11/24
// STAR:
// SKILL: 
// TRAP:
typedef unsigned long long ULL;
// WAYS is the number of combinations of triangles from 1...n
vector<ULL> WAYS;

void init() {
    for (ULL n=0;n<4;++n) {
        WAYS.push_back(0);
    }
    for (ULL n=4;n<=1e6;++n) {
        ULL d;
        if (n % 2 == 0) {
            d = (n-1)/2;
        } else {
            d = (n-3)/2;
        }
        ULL x = d*(n-d-2);
        WAYS.push_back(x+WAYS[n-1]);
    }
}

int main() {
    init();
    ULL n;
    while (cin >> n) {
        if (n < 3) break;
        cout << WAYS[n] << endl;
    }
}
