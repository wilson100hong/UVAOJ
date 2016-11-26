#include <iostream>
#include <vector>
#include <set>
using namespace std;

// 2016/11/25
// STAR:
// SKILL:
// TRAP:
//

bool check(const vector<int>& numbers) {
    set<int> comb;
    comb.insert(0);
    for (int n : numbers) {
        if (comb.count(n)) {
            return false;
        }
        set<int> to_add;
        for (int c : comb) {
            to_add.insert(c + n);
        }
        comb.insert(to_add.begin(), to_add.end());
    }
    return true;
}

int main() {
    int D;
    int cases = 1;
    while (cin >> D) {
        cout << "Case #" << cases << ":";
        vector<int> numbers;
        bool ok = true;
        int prev = -1;
        for (int i=0;i<D;++i) {
            int n;
            cin >> n;
            if (n <= prev) {
                ok = false;
            }
            cout << " " << n;
            numbers.push_back(n);
            prev = n;
        }
        cout << endl;
        if (ok) {
            ok = check(numbers);
        }
        if (ok) {
            cout << "This is an A-sequence." << endl;
        } else {
            cout << "This is not an A-sequence." << endl;
        }
        cases++;
    }
}
