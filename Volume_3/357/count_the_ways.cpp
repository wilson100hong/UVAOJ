// NOTE:
//   1. numbers in dp array is huge, use long long int
//   2. (i - coins[c] >= 0)
#include <iostream>
#include <vector>
using namespace std;

#define MAX 30000

int main() {
  vector<long long int> dp(MAX + 1, 1.0);
  vector<int> coins = {1, 5, 10, 25, 50};

  for (int c = 1; c < coins.size(); ++c) {
    for (int i = 1; i <= dp.size(); ++i) {
      if (i - coins[c] >= 0) {
        dp[i] += dp[i - coins[c]];
      }
    }
  }

  int n;
  while (cin >> n) {
    long long int ans = dp[n];
    if (ans == 1) {
      cout << "There is only 1 way to produce " << n << " cents change." << endl;
    } else {
      cout << "There are " << ans << " ways to produce " << n << " cents change." << endl;
    }
  }
}
