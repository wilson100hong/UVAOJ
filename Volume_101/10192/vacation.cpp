#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}
int max(int a, int b, int c) {
    return max(a, max(b,c));
}

int dp[200][200];

int solve(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    for (int i=0;i<200;++i)
        for (int j=0;j<200;++j)
            dp[i][j] = 0;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + (s1[i-1] == s2[j-1] ? 1 : 0));
        }
    }

    return dp[n][m];
}

int main() {
    string s1, s2;
    int t=1;
    while (true) {
        getline(cin, s1);
        if (s1 == "#" || s1[0] == '#') break;
        getline(cin, s2);
        cout << "Case #" << t++ << ": you can visit at most " << solve(s1, s2) << " cities." << endl;
    }   
}
