// 2016/10/05
// STAR: **
// SKILL: bridge
// TRAP: could be forest
//       compare pre (order) 
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <utility>
#include <limits>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

void dump(const vector<set<int>>& graph) {
  for (int u=0;u<graph.size();++u) {
    cout << u << ":";
    for (int v : graph[u]) {
      cout << " " << v;
    }
    cout << endl;
  }
}

int min(int a, int b) {
  return a < b ? a : b;
}

void dfs(const vector<set<int>>& graph,
    vector<int>& low,
    vector<int>& order,
    int& pre,
    int parent,
    int node,
    set<pair<int, int>>& bridges) {
  low[node] = numeric_limits<int>::max();
  order[node] = pre++;
  for (int child : graph[node]) {
    if (child != parent) {
      if (order[child] == -1) {
        dfs(graph, low, order, pre, node, child, bridges);
        if (low[child] > order[node]) {
          if (node < child) {
            bridges.insert({node, child});
          } else {
            bridges.insert({child, node});
          }
        }
        low[node] = min(low[node], low[child]);
      } else {
        // back edge
        low[node] = min(low[node], order[child]);
      }
    }
  }
}

void solve(const vector<set<int>>& graph) {
  // find all bridges
  int n = graph.size();
  vector<int> low(n, -1);
  vector<int> order(n, -1);
  set<pair<int, int>> bridges;
  int pre = 0;
  for (int root=0;root<n;++root) {
    if (order[root] == -1) {
      dfs(graph, low, order, pre, -1, root, bridges);
    }
  }
  cout << bridges.size() << " critical links" << endl;
  for (const auto& bridge : bridges) {
    cout << bridge.first << " - " << bridge.second << endl;
  }
  cout << endl;
}

int main() {
  int N;
  while (eatline() >> N) {
    vector<set<int>> graph(N, set<int>());
    for (int i=0;i<N;++i) {
      stringstream& ss = eatline();
      int u, ne;
      ss >> u;
      char dummy;
      ss >> dummy;  // '('
      ss >> ne;
      ss >> dummy;  // ')'
      for (int e=0;e<ne;++e) {
        int v;
        ss >> v;
        graph[u].insert(v);
        graph[v].insert(u);
      }
    }
    solve(graph);
    eatline();
  }
}
