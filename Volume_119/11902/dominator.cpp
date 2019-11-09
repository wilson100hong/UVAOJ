#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;


void dfs(const vector<set<int>>& graph, int u, int ignored, set<int>& visited) {
  if (u == ignored) return;

  visited.insert(u);
  for (int v : graph[u]) {
    if (u == v || v == ignored || visited.count(v)) continue;
    dfs(graph, v, ignored, visited);
  }
}

void print_divider(int n) {
  cout << "+";
  for (int i=0;i<2*n-1;++i) {
    cout << "-";
  }
  cout << "+" << endl;
}

void solve(const vector<set<int>>& graph, const vector<set<int>>& pred) {
  int n = graph.size();
  // 1. DFS to find not reachable nodes
  set<int> reachable;
  dfs(graph, 0, -1, reachable);

  // 2. Get dominators
  vector<vector<bool>> dominators(n, vector<bool>(n, false));
  for (int u : reachable) {
    set<int> visited;
    dfs(graph, 0, u, visited);

    for (int v : reachable) {
      if (!visited.count(v)) {
        dominators[u][v] = true;
      }
    }
  }
  
  // 3. Print
  print_divider(n);
  for (int i=0;i<n;++i) {
    cout << "|";
    for (int j=0;j<n;++j) {
      // Transpose matrix
      cout << (dominators[i][j] ? "Y" : "N");
      cout << "|";
    }
    cout << endl;
    print_divider(n);
  }
}

int main() {
  int T;
  cin >> T;
  for (int t=1;t<=T;++t) {
    int N;
    cin >> N;
    vector<set<int>> graph(N, set<int>());
    vector<set<int>> pred(N, set<int>());
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        int x;
        cin >> x;
        if (x == 1) {
          graph[i].insert(j);
          pred[j].insert(i);
        }
      }
    }

    cout << "Case " << t << ":" << endl;
    solve(graph, pred);
  }
}
