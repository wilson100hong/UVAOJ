#include <iostream>
#include <vector>
#include <set>

int abs(int a) {
    return a > 0 ? a: -a;
}

using namespace std;
struct Constraint{
    int a;
    int b;
    int c;
};

int satisfy(const vector<int>& sofar, const vector<Constraint>& constraints) {
    int n = sofar.size();
    vector<int> pos(n, -1);
    for (int i=0;i<n;++i) {
        pos[sofar[i]] = i;
    }
    for (const Constraint ct: constraints) {
        int dist = abs(pos[ct.a] - pos[ct.b]);
        if ((ct.c > 0 && dist > ct.c) || (ct.c < 0 && dist < -ct.c)) {
            return false;
        }
    }
    return true;
}


int solve(int n, const vector<Constraint>& constraints,
        vector<int>& sofar,
        vector<bool>& used) {
    if (sofar.size() == n) {
        return satisfy(sofar, constraints);
    }
    int ans = 0;
    for (int i=0;i<n;++i) {
        if (!used[i]) {
            sofar.push_back(i);
            used[i] = true;
            ans += solve(n, constraints, sofar, used);
            used[i] = false;
            sofar.pop_back();
        }
    }
    return ans;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<Constraint> constraints;
        for (int i=0;i<m;++i) {
            Constraint ct;
            cin >> ct.a >> ct.b >> ct.c;
            constraints.push_back(ct);
        }
        // brute force: generate all combinations, then filtering
        vector<bool> used(n, false);
        vector<int> sofar;
        cout << solve(n, constraints, sofar, used) << endl;
    }
}
