// 1. Check connectivity (dfs)
// 2. You need to start vertex that has non-zero degree
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

#define COLOR_MAX 50
using namespace std;

vector<vector<int>> graph;
vector<bool> visit;
vector<int> route;

int dfs(int u) {
  visit[u]= true;
  int accum = 1;
  for (int v = 0; v < graph[u].size(); ++v) {
    if (graph[u][v] > 0 && !visit[v]) {
      accum += dfs(v);
    }
  }
  return accum;
}

bool is_connected_eular() {
  int num_v = 0, start = -1;
  // vertex degree should be even
  for (int u = 0; u < graph.size(); ++u) {
    int degree = 0;
    for (int v = 0; v < graph[u].size(); ++v) {
      degree += graph[u][v];
    }
    if (degree % 2 != 0) 
      return false;

    if (degree > 0) {
      num_v++;
      if (start == -1) start = u;
    }
  }
  // check connected
  if (dfs(start) != num_v)  return false;
  return true;
}

void rec(int u) {
  for (int v = 0; v < graph[u].size(); ++v) {
    if (graph[u][v] > 0) {
      graph[u][v]--; graph[v][u]--;
      rec(v);
    }
  }
  // no more edge, at the end of cycle
  route.push_back(u);
}

int main() {
  int round;
  cin >> round;

  for (int tc = 1; tc <= round; tc++) {
    int n;
    cin >> n;
    graph.clear();
    graph.assign(COLOR_MAX, vector<int>(COLOR_MAX, 0));
    visit.clear();
    visit.assign(COLOR_MAX, false);
    int start = -1;
    for (int i = 0; i < n; ++i) {
      int a, b;
      cin >> a >> b;
      a--; b--;
      graph[a][b]++; graph[b][a]++;
      if (start == -1)
        start = a;
    }

    if (tc > 1) cout << endl;
    cout << "Case #" << tc << endl;

    if (!is_connected_eular()) {
      cout << "some beads may be lost" << endl;
      continue;
    }
    route.clear();
    rec(start);
    // print route
    while (route.size() > 1) {
      int a = route.back();
      route.pop_back();
      int b = route.back();
      cout << a+1 << " " << b+1 << endl;
    }
  }
}
