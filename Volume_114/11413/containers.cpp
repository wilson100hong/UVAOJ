#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
bool satisfy(const vector<int>& vessels, int containers, LL cap) {
    // greddy
    int c = 0;  // container index
    int left = cap;
    for (int v : vessels) {
        while ((left < v) && (c < containers)) {
            c++;
            left = cap;
        }
        if (c == containers) return false;
        left -= v;
    }
    return true;
}
int solve(const vector<int>& vessels, int m) {
    LL sum = 0;
    for (int v : vessels) {
        sum += v;
    }
    LL L=1, R=sum;
    while (R > L) {
        LL M = (L + R) / 2;
        if (satisfy(vessels, m, M)) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    return R;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> vessels;
        for (int i=0;i<n;++i) {
            int v;
            cin >> v;
            vessels.push_back(v);
        }

        cout << solve(vessels, m) << endl;
    }
}
