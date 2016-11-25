#include <iostream>
using namespace std;

// 2016/11/24
// STAR:
// SKILL:
// TRAP

typedef unsigned long long ULL;

ULL next(ULL N, ULL a, ULL b, ULL cur) {
    // (a*cur*cur + b) % N
    ULL res = (cur*cur) % N;
    res = (a*res) % N;
    return (res + b) % N;
}

ULL solve(ULL N, ULL a, ULL b) {
    // 1. find an element in cycle
    ULL first = 0;
    ULL second = 0;
    while (1) {
        first = next(N, a, b, first);
        second = next(N, a, b, next(N, a, b, second));
        if (first == second) break;
    }
    // 2. find cycle length
    ULL cur = first;
    ULL cnt = 1;
    while (1) {
        cur = next(N, a, b, cur);
        if (cur == first) break;
        cnt++;
    }
    return N - cnt;
}

int main() {
    ULL N, a, b;
    while (cin >> N) {
        if (N == 0) break;
        cin >> a >> b;
        cout << solve(N, a, b) << endl;
    }
}
