// The main idea is to make the graph an euler circuit.
// This can be done by making all nodes to have even degree.
// state is a bit mask. 0 means the vertex has even edges, 1 means odd edge.
// dp[state] is the min cost starting from state to dp[0].
// The most important thing is every time we flip two 1's in state.
// lets said 1 at index i and j. o[i] is the mapping index
// dp[state] = dist[o[i]][o[j]] + dp[state - (1<<i) - (1<<j)]
// it basically try all combination of pairs and pick the best,
// so no need to worry about we add more than 1 edges on existing edge.
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// this trick lets MAX + n still > 0
int MAX = numeric_limits<int>::max()/2;

int min(int a, int b) {
  return a < b ? a : b;
}

int rec(const vector<vector<int>>& graph, const vector<int>& odds,
    vector<int>& dp, int state) {
  if (dp[state] != MAX)
    return dp[state];

  int n = odds.size();
  for (int i = 0; i < n; ++i) {
    if ((state>>i) & 1) {
      for (int j = i + 1; j < n; ++j) {
        if ((state>>j) & 1) {
          dp[state] = min(dp[state],
              graph[odds[i]][odds[j]] + rec(graph, odds, dp, state - (1<<i) - (1<<j)));
        }
      }
    }
  }
  return dp[state];
}

int solve(const vector<vector<int>>& graph,
    const vector<int>& odds) {
  int no = odds.size();
  int state = (1<<no) - 1;
  vector<int> dp((1<<no), MAX);
  dp[0] = 0;
  return rec(graph, odds, dp, state);
}

int main() {
  int N, M;
  while (cin >> N) {
    if (N == 0) break;
    cin >> M;
    int sum = 0;
    vector<vector<int>> graph(N+1, vector<int>(N+1, MAX));
    vector<int> degree(N+1, 0);
    for (int m = 0; m < M; ++m) {
      int u, v, length;
      cin >> u >> v >> length;
      graph[v][u] = graph[u][v] = min(graph[u][v], length);
      sum += length;
      degree[u]++;
      degree[v]++;
    }
    
    // Floyd Warshall
    for (int i = 1; i <= N; ++i)
      graph[i][i] = 0;
    for (int k = 1; k <= N; ++k) {
      for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
          graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        }
      }
    }

    vector<int> odds;
    for (int i = 1; i <= N; ++i) {
      if (degree[i] % 2 != 0) {
        odds.push_back(i);
      }
    }
    int ans = sum + solve(graph, odds);
    cout << ans << endl;
  }
}
