#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <stack>
using namespace std;
// 2016/10/11
// SKILL: longest path, topological sort
// STAR: *
// TRAP: 1) when tie, pick lowest end
//       2) if path len = 0, end = start!

int max(int a, int b) {
  return a > b ? a : b;
}

void dfs(vector<set<int>>& graph, int u, vector<bool>& visit, stack<int>& post) {
  visit[u] = true;
  for (int v : graph[u]) {
    if (!visit[v]) {
      dfs(graph, v, visit, post);
    }
  }
  post.push(u);
}

pair<int, int> solve(vector<set<int>>& graph, int s) {
  int n = graph.size();
  // 1. topological sort
  stack<int> post;
  vector<bool> visit(n, false);
  dfs(graph, s, visit, post);

  // since graph all reachable from s and acyclic, s should be the first
  vector<int> dist(n, 0);
  int longest = 0;
  int end = s;
  while (!post.empty()) {
    int u = post.top();
    post.pop();
    if (dist[u] > longest || (dist[u] == longest && u < end)) {
      longest = dist[u];
      end = u;
    }
    for (int v : graph[u]) {
      dist[v] = max(dist[v], dist[u] + 1);
    }
  }

  return {longest, end};
}

int main() {
  int n, s, p, q;
  int cases=1;
  while (cin >> n) {
    if (n==0) break;
    cin >> s;
    vector<set<int>> graph(n+1, set<int>());
    while (cin >> p >> q) {
      if (p==0&&q==0) break;
      graph[p].insert(q);
    }
    pair<int, int> ans = solve(graph, s);
    cout << "Case " << cases << ": The longest path from " << s;
    cout << " has length " << ans.first << ", finishing at " << ans.second << "." << endl;
    cout << endl;
    cases++;
  }
}
