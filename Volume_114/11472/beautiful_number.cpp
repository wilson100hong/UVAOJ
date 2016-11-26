#include <iostream>
#include <vector>
using namespace std;

// 2016/11/26
// STAR: **
// SKILL: DP
// TRAP: 1) M = 0

typedef unsigned long long ULL;

ULL MOD = 1000000007;

ULL solve(int N, int M) {
    if (M < N) return 0;
    // 3d array [len][digit][used]
    // len: length of number
    // digit: ending digit of number
    // used: used numbers, bitmask
    vector<vector<vector<ULL>>> dp(M+1, vector<vector<ULL>>(N, vector<ULL>(1<<N, 0)));

    // init for number with length == 1
    for (int n=1;n<N;++n) {
        dp[1][n][(1<<n)] = 1;
    }
    
    for (int m=1;m<M;++m) {
        for (int n=0;n<N;++n) {
            for (int state = 0; state<(1<<N);++state) {
                if (dp[m][n][state] == 0) continue;
                for (int nn : {n-1, n+1}) {
                    if (0<=nn && nn<N) {
                        dp[m+1][nn][state | (1<<nn)] += dp[m][n][state];
                        dp[m+1][nn][state | (1<<nn)] %= MOD;
                    }
                }
            }
        }
    }

    ULL res = 0;
    for (int m=N;m<=M;++m) {
        for (int n=0;n<N;++n) {
            res = (res + dp[m][n][(1<<N)-1]) % MOD;
        }
    }
    return res;
}

int main() {
    int T, N, M;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        cout << solve(N, M) << endl;
    }
}
