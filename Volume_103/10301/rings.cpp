#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Ring{
    double x;
    double y;
    double r;
};

bool overlap(const Ring& r1, const Ring& r2) {
    double dx = r1.x-r2.x;
    double dy = r1.y-r2.y;
    
    double d2 = dx*dx + dy*dy;
    return (r1.r-r2.r)*(r1.r-r2.r) < d2 && d2 < (r1.r+r2.r)*(r1.r+r2.r);
}

int solve(const vector<Ring>& rings) {
    vector<bool> visited(rings.size(), false);
    queue<int> q;
    int ret = 0;
    for (int i=0;i<rings.size();++i) {
        int max = 0;
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);
        }
        // BFS and update max here
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            max++;
            for (int j=0;j<rings.size();j++) {
                if (!visited[j] && overlap(rings[front], rings[j])) {
                    //cout << "j: " << j << endl;
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
        if (max > ret) ret = max;
    }
    return ret;
}

int main() {
    int N;
    while (cin >> N) {
        if (N  == -1) break;
        vector<Ring> rings;
        while(N--) {
            Ring ring;
            cin >> ring.x >> ring.y >> ring.r;
            rings.push_back(ring);
        }
        int m = solve(rings);
        cout << "The largest component contains " << m << " ring";
        if (m != 1) cout << "s";
        cout << "." << endl;
    }
}
