#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 2016/11/26
// STAR: ****
// SKILL: DP, see http://www.cnblogs.com/tuty/p/4856636.html
// TRAP: 1) use 2-D dp array
//       2) A[i][j] = 1 for i <= j !

double solve(int n, double p) {
    vector<double> pow(n+1, 1.0);
    vector<double> ipow(n+1, 1.0);
    for (int i=1;i<=n;++i) {
        pow[i] = pow[i-1]*p;
        ipow[i] = ipow[i-1]*(1.0-p);
    }


    // let A[i][j] be the probability of "in i games, winning-streak <= j"
    // then we will have:
    // 0) A[i][j] = 1, when i <= j
    // 1) A[i][0] = (1-p)^i
    // 2) A[i][i-1] = 1 - p^i
    // 3) for 0<j<i-1, A[i][j] = A[i-1][j] - prob({all cases in A[i-1][j] which could produce winning-streak > j by appending W})
    //    this only happens when there is trailing winning-streak with j+1:
    //    |<-- i-j-2 -->| |<-- j+1 -->|
    //    ...............LWW.........WW
    //    so prob({all cases in A[i-1][j] which could produce winning-streak > j by appending W})
    //    = A[i-j-2][j] * (1-p) * p^(j+1)
    //      ~~~~~~~~~~~   ~~~~~   ~~~~~~~
    //      first part  lose   trailing winnings
    
    // The probability of "in i games, winning-strek = j" is then A[i][j] - A[i][j-1]
    
    vector<vector<double>> A(n+1, vector<double>(n+1, 0.0));
    for (int i=0;i<=n;++i) {
        for (int j=0;j<=n;++j) {
            if (i <= j) {
                A[i][j] = 1.0;
            } else if (j==0) {
                A[i][j] = ipow[i];
            } else if (j==i-1) {
                A[i][j] = 1 - pow[i];
            } else {
                A[i][j] = A[i-1][j] - A[i-j-2][j]*(1.0-p)*pow[j+1];
            }
        }
    }
    double res = 0.0;
    for (int k=1;k<=n;++k) {
        res += k*(A[n][k] - A[n][k-1]);
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
