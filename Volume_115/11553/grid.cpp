#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits>
using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

int MAX = 50000;

int rec(const vector<vector<int>>& grids, int n, int col, vector<bool>& rows) { 
    // Maximum values we can get from grids for each column, where row not intersect.
    // Similar to Queen's chessboard.
    if (col == n) return 0;
    
    int best_value = MAX;
    for (int r=0;r<n;++r) {
        if (!rows[r]) {
            rows[r] = true;
            int value = grids[r][col] + rec(grids, n, col+1, rows);
            rows[r] = false;
            best_value = min(value, best_value);
        }
    }
    return best_value;
}

int solve(const vector<vector<int>>& grids) {
    int n = grids.size();
    vector<bool> rows(n, false);
    //vector<int> DP(1<<n, MAX);
    // optimize: pruning
    
    return rec(grids, n, 0, rows);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> grids(n, vector<int>(n, 0));
        for (int i=0;i<n;++i) {
            for (int j=0;j<n;++j) {
                int v;
                cin >> v;
                grids[i][j] = v;
            }
        }
        set<int> rows;
        cout << solve(grids) << endl;
    }
}
