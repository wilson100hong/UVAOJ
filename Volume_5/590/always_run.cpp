#include <iostream>
#include <vector>
using namespace std;

#define INF 1 << 30

int cost(vector<vector<vector<int>>>& graph, int K, int n, int m, int k) {
  int cycle = graph[n][m].size();
  return cycle == 0 ? 0 : graph[n][m][(K - k) % cycle];
}

int solve(vector<vector<vector<int>>>& graph, int K) {
  // 2d DP arary, dp[k][u] means the min cost starting from node u, after k
  // days, to graph[N - 1]. 
  int N = graph.size();
  vector<vector<int>> dp(K + 1, vector<int>(N, INF));

  dp[0][N-1] = 0;
  for (int k = 1; k <= K; ++k) {
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < N; ++m) {
        if (m == n) 
          continue;
        int cur_cost = cost(graph, K, n, m, k);
        if (cur_cost > 0 && dp[k-1][m] != INF
            && cur_cost + dp[k-1][m] < dp[k][n]) {
          dp[k][n] = cur_cost + dp[k-1][m];
        }
      }
    }
  }
  return dp[K][0];
}

int main() {
  int N, K, T = 1;
  while (1) {
    cin >> N >> K;
    if (N == 0 && K == 0)
      break;
    vector<vector<vector<int>>> graph;
    for (int n = 0; n < N; ++n) {
      vector<vector<int>> edges;
      for (int m = 0; m < N; ++m) {
        vector<int> costs;
        if (n != m) {
          int cycle, tmp;
          cin >> cycle;
          while (cycle-- > 0) {
            cin >> tmp;
            costs.push_back(tmp);
          }
        }
        edges.push_back(costs);
      }
      graph.push_back(edges);
    }
    cout << "Scenario #" << T << endl;
    int ans = solve(graph, K);
    if (ans < INF) {
      cout << "The best flight costs " << ans << "." << endl;
    } else {
      cout << "No flight possible." << endl;
    }
    cout << endl;
    T++;
  }
}
