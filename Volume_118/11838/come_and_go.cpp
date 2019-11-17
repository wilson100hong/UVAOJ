#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

void dfs(vector<set<int>>& graph, int u, set<int>& visit, vector<int>& post) {
  visit.insert(u);
  for (int v : graph[u]) {
    if (visit.count(v)) continue;
    dfs(graph, v, visit, post);
  }
  post.push_back(u);
}


int solve(vector<set<int>>& graph) {
  int N = graph.size();
  set<int> visit;
  vector<int> post;

  for (int u=0;u<N;++u) {
    if (!visit.count(u)) {
      dfs(graph, u, visit, post);
    }
  }

  vector<set<int>> rev_graph(N, set<int>());
  for (int u=0;u<N;++u) {
    for (int v : graph[u]) {
      rev_graph[v].insert(u);
    }
  }

  int sink = post[N-1];
  visit.clear();
  post.clear();
  dfs(rev_graph, sink, visit, post);
  return visit.size() == N ? 1 : 0;
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    vector<set<int>> graph(N, set<int>());
    while (M--) {
      int u, v, x;
      cin >> u >> v >> x;
      u--;
      v--;
      graph[u].insert(v);
      if (x == 2) {
        graph[v].insert(u);
      }
    }
    cout << solve(graph) << endl;
  }
}
