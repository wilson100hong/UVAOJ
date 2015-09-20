#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_NODE 2000

void dfs(vector<vector<int>>& g, int u, vector<bool>& visit, vector<int>& sorted) {
  visit[u] = true;
  for (int v : g[u]) {
    if (!visit[v]) {
      dfs(g, v, visit, sorted);
    }
  }
  sorted.push_back(u);
}

int main() {
  int n;
  int first = 0;
  while (cin >> n) {
    int i, j, k;
    vector<vector<int>> g(MAX_NODE, vector<int>());
    for(i = 0; i < n; i++) {
      int outdeg;
      cin >> outdeg;
      for(j = 0; j < outdeg; j++) {
        cin >> k;
        g[i].push_back(k);
      }
    }

    vector<bool> visit(MAX_NODE, false);
    vector<int> sorted;
    dfs(g, 0, visit, sorted);

    vector<int> dp(MAX_NODE, 0);
    dp[0] = 1;
    for (int i = sorted.size() - 1; i >= 0; --i) {
      int u = sorted[i];
      for (int v : g[u]) {
        dp[v] += dp[u];
      }
    }

    int ans = 0;
    for(i = 0; i < n; i++)
      if(g[i].size() == 0) 
        ans += dp[i];
    if (first) cout << endl;
    first = 1;
    cout << ans << endl;
  }
  return 0;
}
