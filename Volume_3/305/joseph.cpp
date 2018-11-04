#include <iostream>
#include <vector>
using namespace std;

void dump(int round, const vector<bool>& ring) {
    cout << "round #" << round << ":" << endl;
    for (bool b : ring) {
        if (b) cout << "T";
        else cout << "F";
    }
    cout << endl;
}

bool good(int k, int m) {
    // cout << "try m: " << m << endl;
    // init
    int n = 2*k;
    int v = 0;  // victim
    for (int i=0;i<k;++i) {
        v = (v + m - 1) % (n - i);
        // cout << "  round " << i << ",  victim: " << v << endl;
        if (v < k) {
            return false;
        }
    }
    return true;
}

// TODO: prebuild table.
int solve(int k) {
    int m = k+1; 
    while (true) {
        if (good(k, m)) {
            return m;
        }
        m++;
        if ((m-1)%(2*k) == 0) {
            m += k;
        }
    }
}

int main() {
    vector<int> answer(14, 0);
    for (int i=1;i<14;++i) {
        answer[i] = solve(i);
    }
    
    int k;
    while (cin >> k) {
        if (k == 0) break;
        cout << answer[k] << endl;
    }
}
