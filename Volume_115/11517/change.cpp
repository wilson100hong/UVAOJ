#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>

using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

pair<int, int> solve(const vector<int>& bills, int price) {
  int bound = 1+price+bills[bills.size()-1];

  vector<int> dp(bound, -1);
  dp[0] = 0;
  int min_amount = -1, min_cnt = -1;
  for (int i=0;i<bills.size();++i) {
    vector<int> ndp = dp;  // maybe need optimize
    for (int p=1; p<bound;++p) {
      int lp = p-bills[i];
      if (lp >= 0 && dp[lp] >= 0) {
        // need update
        if (dp[p] == -1 || dp[lp]+1 < ndp[p]) {
          ndp[p] = dp[lp] + 1;
          // achive goal
          if (p >= price) {
            if (min_amount == -1 || p < min_amount) {
              min_amount = p;
              min_cnt = ndp[p];
            } else if (p == min_amount && ndp[p] < min_cnt) {
              min_cnt = ndp[p];
            }
          }
        }
      }
    }
    dp = ndp;
  }
  return {min_amount, min_cnt};
}

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int price;
    cin >> price;
    int n;
    cin >> n;
    vector<int> bills(n, 0);
    for (int i=0;i<n;++i) {
      cin >> bills[i];
    }
    sort(bills.begin(), bills.end());
    int total, cnt;
    tie(total, cnt) = solve(bills, price);
    cout << total << " " << cnt << endl;
  }
}
