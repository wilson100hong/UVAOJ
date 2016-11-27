#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 2016/11/26
// STAR: ***
// SKILL: DP
// TRAP: 1) 

// calculate:
double solve(int n, double p) {
    // TODO: use 2d dp
    double ip = 1.0-p; // inverse p

    // (len, winning-streak, tailing-winnding)
    vector<vector<vector<double>>> dp(n+1, vector<vector<double>>(n+1, vector<double>(n+1, 0.0)));
    // init
    dp[0][0][0] = 1.0;
    for (int len=0;len<n;++len) {
        for (int ws=0;ws<=len;++ws) {
            for (int tw=0;tw<=len;++tw) {
                dp[len+1][ws][0] += dp[len][ws][tw]*ip;
                if (tw+1 > ws) {
                    dp[len+1][tw+1][tw+1] += dp[len][ws][tw]*p;
                } else {  // tw <= ws
                    dp[len+1][ws][tw+1] += dp[len][ws][tw]*p;
                }
            }
        }
    }
    double res = 0.0;
    for (int ws=0;ws<=n;++ws) {
        for (int tw=0;tw<=n;++tw) {
            res += ws*dp[n][ws][tw];
        }
    }
    return res;
}

int main() {
    int n;
    double p;
    while (cin >> n >> p) {
        if (n==0) break;
        cout << fixed;
        cout << setprecision(10) << solve(n, p) << endl;
    }
}
