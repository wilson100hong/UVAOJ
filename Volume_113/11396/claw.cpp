#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

constexpr int kNone = -1;
constexpr int kCenter = 0;
constexpr int kCorner = 1;

bool dfs(const vector<set<int>>& graph, int u, int label, vector<int>& labels) {
  labels[u] = label;

  int new_label = (label + 1) % 2;
  for (int v : graph[u]) {
    if (labels[v] == kNone) {
      if(!dfs(graph, v, new_label, labels)) {
        return false;
      }
    } else if (labels[v] == label) {
      return false;
    } else {  // labels[v] == new_label
      ;
    }
  }
  return true;
}

string solve(const vector<set<int>>& graph) {
  int N = graph.size();
  vector<int> labels(N, kNone);
  bool ok = true;
  for (int u=0;u<N;++u) {
    if (labels[u] != kNone) continue;
    if (!dfs(graph, u, kCenter, labels)) {
      ok = false;
      break;
    }
  }

  return ok ? "YES" : "NO";
}

int main() {
  int N;
  while (cin >> N) {
    if (N==0) break;
    vector<set<int>> graph(N, set<int>());
    int u, v;
    while (cin >> u >> v) {
      if (u == 0 && v == 0) break;
      u--;
      v--;
      graph[u].insert(v);
      graph[v].insert(u);
    }
    cout << solve(graph) << endl;
  }
}
