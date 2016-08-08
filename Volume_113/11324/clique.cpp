#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;

void DFS(const vector<set<int>>& graph,
    int u,
    vector<bool>& visit,
    stack<int>& stk) {
  visit[u] = true;
  for (int v : graph[u]) {
    if (!visit[v]) {
      DFS(graph, v, visit, stk);
    }
  }
  stk.push(u);
}

vector<set<int>> SCC(const vector<set<int>>& graph) {
  int n = graph.size();
  vector<bool> visit(n, false);
  stack<int> stk;
  for (int u = 0; u < n; ++u) {
    if (!visit[u]) {
      DFS(graph, u, visit, stk);
    }
  }

  // trasnpose graph'
  vector<set<int>> transgraph(n, set<int>());
  for (int u = 0; u < n; ++u) {
    for (int v : graph[u]) {
      transgraph[v].insert(u);
    }
  }

  vector<set<int>> groups;
  // DFS on graph'
  visit.assign(n, false);
  while (!stk.empty()) {
    int u = stk.top();
    stk.pop();
    stack<int> group;
    if (!visit[u]) {
      DFS(transgraph, u, visit, group);
      groups.push_back(set<int>());
      while (!group.empty()) {
        int c = group.top();
        group.pop();
        groups[groups.size()-1].insert(c);
      }
    }
  }
  return groups;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int solve(const vector<set<int>>& graph) {
  // 1. SCC
  vector<set<int>> groups = SCC(graph);

  // 2. vertex to group look up
  map<int, int> lookup;
  for (int g = 0; g < groups.size(); ++g) {
    for (int u : groups[g]) {
      lookup[u] = g;
    }
  }

  // 3. contract graph G'
  vector<set<int>> metagraph(groups.size(), set<int>());
  for (int u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      int mu = lookup[u];
      int mv = lookup[v];
      if (mu != mv) {
        metagraph[lookup[u]].insert(lookup[v]);
      }
    }
  }

  // 4. find longest path in G' using topological sort
  int best = 0;
  vector<bool> visit(metagraph.size(), false);
  stack<int> ordering;
  vector<int> dp(metagraph.size(), 0);
  for (int mu = 0; mu < metagraph.size(); ++mu) {
    dp[mu] = groups[mu].size();
    best = max(best, dp[mu]);
    if (!visit[mu]) {
      DFS(metagraph, mu, visit, ordering);
    }
  }
  while (!ordering.empty()) {
    int cur = ordering.top();
    ordering.pop();
    for (int next : metagraph[cur]) {
      dp[next] = max(dp[next], dp[cur] + groups[next].size());
      if (dp[next] > best) {
        best = dp[next];
      }
    }
  }
  return best;
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds--) {
    int N, M;
    cin >> N >> M;
    vector<set<int>> graph(N, set<int>());

    for (int m = 0; m < M; ++m) {
      int u, v;
      cin >> u >> v;
      u--; v--;
      graph[u].insert(v);
    }
    cout << solve(graph) << endl;
  }
}
