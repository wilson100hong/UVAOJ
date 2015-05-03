// NOTE: when updating dp, be aware that the update actually happens "next round",
// you * SHOULD NOT* update current round statd dp!
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_VALUE 500

int main() {
  int T, M, C;
  cin >> T;
  vector<int> coins;

  while (T-- > 0) {
    coins.clear();
    cin >> M;
    int sum = 0;
    while(M-- > 0) {
      cin >> C;
      coins.push_back(C);
      sum += C;
    }
    sort(coins.begin(), coins.end());

    // The goal is to find some partition = sum / 2
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    vector<int> tmp;
    for (const int& coin : coins) {
      if (coin > target) break;
      tmp.clear();
      for (int i = 0; i < dp.size() && i + coin <= target; ++i) {
        if (dp[i]) {
          tmp.push_back(i + coin);
        }
      }
      for (const int& t : tmp) {
        dp[t] = true;
        if (t == target) 
          break;
      }
    }

    int ans = 0;
    for (int i = dp.size() - 1; i >= 0; --i) {
      if (dp[i]) {
        ans = sum - i - i;
        break;
      }
    }
    cout << ans << endl;
  }
}
