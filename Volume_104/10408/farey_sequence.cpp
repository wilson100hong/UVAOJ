#include <iostream>
#include <string>
using namespace std;

// 2016/11/25
// STAR: *
// SKILL: Farey sequence: https://en.wikipedia.org/wiki/Farey_sequence#Next_term
// TRAP:

struct Fraction {
    int n;  // nominator
    int d;  // denominator
};

string f2s(const Fraction& f) {
    return to_string(f.n) + "/" + to_string(f.d);
}

string solve(int n, int k) {
    Fraction f0 = {0, 1};
    Fraction f1 = {1, n};
    if (k == 1) return f2s(f1);

    for (int i=2;i<=k;++i) {
        int k = (n+f0.d)/f1.d;
        int p = k*f1.n - f0.n;
        int q = k*f1.d - f0.d;
        f0 = f1;
        f1 = {p, q};
    }
    return f2s(f1);
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        cout << solve(n, k) << endl;
    }
}
