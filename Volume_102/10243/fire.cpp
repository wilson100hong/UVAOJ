// NOTE:
//   1. whole graph can be multiple components
//   2. single node should have one exit
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

#define INF 1 << 30

int min(int a, int b) {
  return a < b ? a : b;
}

void dfs(vector<vector<int>>& graph,
         vector<bool>& visit,
         vector<pair<int, int>>& dp,
         int node) {
  visit[node] = true;

  // loop all children
  int first_sum = 1;  // put exit at node
  int second_sum = graph[node].size() > 0 ? 0 : 1;  // don't put exit at node
  for (auto& child : graph[node]) {
    if (!visit[child]) {
      dfs(graph, visit, dp, child);
      first_sum += min(dp[child].first, dp[child].second);  // ATTENTION: should never be INF
      second_sum += dp[child].first;
    }
  }

  dp[node].first = first_sum;
  dp[node].second = second_sum;
}


//  1. graph is a tree
//  2. if any node does not have a fire exit then at
//     least one of its neighbor has.
//  3. for each edge, one of the node must has fire exit.
int solve(vector<vector<int>>& graph) {
  vector<bool> visit(graph.size(), false);
  // dp[i].first:  put exit at i
  // dp[i].second: dont put exit at i
  vector<pair<int, int>> dp(graph.size(), make_pair(INF, INF));

  int ans = 0;
  for (int start = 0; start < graph.size(); start++) {
    if (!visit[start]) {
      dfs(graph, visit, dp, start);
      ans += min(dp[start].first, dp[start].second);
    }
  }
  return ans;
}

int main() {
  int N, E, V;
  while (1) {
    vector<vector<int>> graph;  // 0-based index
    cin >> N;
    if (N == 0)
      break;
    for (int n = 0; n < N; ++n) {
      vector<int> edges;
      cin >> E;
      for (int e = 0; e < E; ++e) {
        cin >> V;
        V--;  // 0-based index
        if (V != n) {
          edges.push_back(V);
        }
      }
      graph.push_back(edges);
    }
    cout << solve(graph) << endl;
  }
}
