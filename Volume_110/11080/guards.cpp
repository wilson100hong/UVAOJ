#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

constexpr int kNone = -1;
constexpr int kGuard = 0;
constexpr int kEmpty = 1;

int dfs(const vector<set<int>>& graph, int u, int state, vector<int>& states, int* total_visit) {
  *total_visit += 1;
  states[u] = state;
  int cost = 0;
  if (state == kGuard) cost++;

  int next_state = (state + 1) % 2;
  for (int v : graph[u]) {
    if (states[v] == state) return -1;
    if (states[v] == next_state) continue;
    // states[v] == kNone
    int a = dfs(graph, v, next_state, states, total_visit);
    if (a == -1) return -1;
    cost += a;
  }
  return cost;
}

// Return number of kGuard. -1 if failed.
int dfs(const vector<set<int>>& graph, int u, vector<int>& states) {
  int total_visit = 0;
  int a = dfs(graph, u, kGuard, states, &total_visit);
  if (a == -1) return -1;

  return max(1, min(a, total_visit - a));
}

int solve(const vector<set<int>>& graph) {
  int N = graph.size();
  vector<int> states(N, kNone);
  int sum = 0;
  for (int u=0;u<N;++u) {
    if (states[u] == kNone) {
      int a = dfs(graph, u, states);
      if (a == -1) return -1;
      sum += a;
    }
  }
  return sum;
}

int main() {
  int T;
  cin >> T;
  int t=1;
  while (t <= T) {
    int N, E;
    cin >> N >> E;
    vector<set<int>> graph(N, set<int>());
    for (int i=0;i<E;++i) {
      int u, v;
      cin >> u >> v;
      graph[u].insert(v);
      graph[v].insert(u);
    }
    cout << solve(graph) << endl;
    t++;
  }
}
