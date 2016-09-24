// Trap: e-moudle is counted by the sum_of_conv^2 + sum_of_it^2
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Coin {
  int conv;
  int it;
};

int solve(const vector<Coin>& coins, int S) {
  vector<vector<int>> dp(S+1, vector<int>(S+1, -1));
  int ans = -1;
  // x: conv  y: it
  int S2 = S*S;
  dp[0][0] = 0;
  for (int x=0;x<S;++x) {
    for (int y=0;y<S;++y) {
      // (x, y) unreachable
      if (dp[x][y] == -1) continue;
      // (x, y) out of bound
      if (x*x+y*y > S2) continue;
      int cnt = dp[x][y] + 1;
      for (const Coin& coin : coins) {
        int nx = x + coin.conv;
        int ny = y + coin.it;
        int ns = nx*nx + ny*ny;
        if (ns > S2) continue; // out of bound
        if (ns == S2) {
          if (ans == -1 || cnt < ans) {
            ans = cnt;
          }
          continue;
        }
        // ns < S2
        if (dp[nx][ny] == -1 || cnt < dp[nx][ny]) {
          dp[nx][ny] = cnt;
        }
      }
    }
  }
  return ans;
}

int main() {
  int cases;
  cin >> cases;
  vector<Coin> coins;
  while (cases--) {
    coins.clear();
    int M, S;
    cin >> M >> S;
    for (int m=0;m<M;++m) {
      int conv, it;
      cin >> conv >> it;
      coins.push_back({conv, it});
    }
    int ans = solve(coins, S);
    if (ans == -1) {
      cout << "not possible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
