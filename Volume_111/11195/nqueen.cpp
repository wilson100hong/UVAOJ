//  1. TLE: use bit operation. a row can be repsented as int
//  2. TLE: use array over vector. It is faster (0.5 sec)
//
// 
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <utility>
using namespace std;

char maps[16][16];

int dfs(int n, int L, int M, int R, int row) {
    if (row == n) return 1;
    int ans = 0;
    for (int i=0;i<n;++i) {
        int ni = (1<<i);
        if (maps[row][i] != '*' && !((L|M|R) & ni)) {
            ans += dfs(n, (L|ni)<< 1, M|ni, (R|ni)>>1 ,row+1);
        }
    }
    return ans;
}

int main() {
    int n;
    int T = 1;
    while (cin >> n) {
        if (n==0) break;
        for (int i=0;i<n;++i) {
            for (int j=0;j<n;++j) {
               char c;
               cin >> maps[i][j];
            }
        }
        cout << "Case " << T++ << ": ";
        cout << dfs(n, 0, 0, 0, 0) << endl;
    }
}
