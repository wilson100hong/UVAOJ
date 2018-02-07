#include <iostream>
#include <algorithm>
using namespace std;

int dp[1001][1001];

int max(int a, int b) {
    return a > b ? a : b;
}

int max(int a, int b, int c) {
    return max(a, max(b, c));
}


int solve(const string& s) {
    int n = s.size();
    string r = s;
    for (int i=0,j=n-1;i<j;++i,--j) {
        swap(r[i], r[j]);
    }


    for (int i=0;i<=1000;++i)
        for (int j=0;j<=1000;++j)
            dp[i][j] = 0;

    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j) {
            dp[i][j] = max(dp[i][j-1], dp[i-1][j], dp[i-1][j-1] + (s[i-1] == r[j-1] ? 1 : 0));
        }
    return dp[n][n];
}

int main() {
    int T;
    string s;
    cin >> T;
    getline(cin, s);
    while (T--) {
        getline(cin, s);
        cout << solve(s) << endl;
    }
}
