#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 2016/11/24
// STAR:
// SKILL:
// TRAP:

// build table from 0 ~ 999

typedef unsigned long long ULL;


ULL expand(ULL n) {
    ULL res = 0;
    while (n) {
        ULL d = n % 10;
        res += d*d;
        n /= 10;
    }
    return res;
}

vector<bool> HAPPY(1000, false);
unordered_set<ULL> DONE;

void init() {
    HAPPY[1] = true;
    DONE.insert(1);
    for (ULL n=2;n<1000;++n) {
        ULL x = n;
        unordered_set<ULL> seen;
        bool is_happy;
        while (1) {
            if (DONE.count(x)) {
                is_happy = HAPPY[x];
                break;
            } else if (seen.count(x)) {
                is_happy = false;
                break;
            }
            seen.insert(x);
            x = expand(x);
        }

        for (ULL y : seen) {
            DONE.insert(y);
            HAPPY[y] = is_happy;
        }
    }
}

int main() {
    init();
    int cases;
    cin >> cases;
    for (int i=1;i<=cases;++i) {
        ULL n;
        cin >> n;
        cout << "Case #" << i << ": " << n << " is " ;
        bool is_happy = HAPPY[expand(n)];
        if (is_happy) {
            cout << "a Happy number." << endl;
        } else {
            cout << "an Unhappy number." << endl;
        }
    }
}
