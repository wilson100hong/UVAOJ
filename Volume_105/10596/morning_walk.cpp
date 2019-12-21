// 1. Disconnected graph, but 0 edge
// 2. Cycle with one noe
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

void DFS(const vector<set<int>>& graph, int u, int& cnt, vector<bool>& visit) {
  visit[u] = true;
  for (int v : graph[u]) {
    if (v == u) cnt++;
    if (!visit[v]) {
      cnt++;
      DFS(graph, v, cnt, visit);
    }
  }
}


bool Solve(const vector<int>& deg, const vector<set<int>>& graph) {
  int N = deg.size();
  for (int d : deg) {
    if (d % 2 != 0) return false;
  }

  // All vertex has even degree
  vector<bool> visit(N, false);
  
  bool has_non_empty = false;
  for (int i=0;i<N;++i) {
    if (!visit[i]) {
      int cnt = 0;
      DFS(graph, i, cnt, visit);
      if (cnt > 0) {
        if (has_non_empty) {
          return false;
        }
        has_non_empty = true;
      }
    }
  }

  return has_non_empty;
}

int main() {
  int N, R;
  
  while (cin >> N >> R) {
    vector<int> deg(N, 0);
    vector<set<int>> graph(N, set<int>());
    int u, v;
    
    for (int r=0;r<R;++r) {
      cin >> u >> v;
      deg[u]++;
      deg[v]++;
      graph[u].insert(v);
      graph[v].insert(u);
    }

    if (Solve(deg, graph)) {
      cout << "Possible" << endl;
    } else {
      cout << "Not Possible" << endl;
    }
  }
}
