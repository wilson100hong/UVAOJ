// 2016/10/05
// STAR: *
// SKILL: articulation
// TRAP: in articulation search, root has different judgement with other nodes
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <limits>

using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

void dfs(const vector<set<int>>& graph,
    vector<int>& pre, 
    vector<int>& low,
    int& label,
    int parent,
    int node, 
    set<int>& arts) {
  pre[node] = label++;
  int subtrees = 0;
  for (int child : graph[node]) {
    if (child != parent) {
      if (pre[child] == -1) {
        subtrees++;
        dfs(graph, pre, low, label, node, child, arts);
        if (parent != -1 && low[child] >= pre[node]) {
          arts.insert(node);
        }
        low[node] = min(low[node], low[child]);
      } else {
        // back edge
        low[node] = min(low[node], pre[child]);
      }
    }
  }

  if (parent == -1 && subtrees >= 2) {
    // root
    arts.insert(node);
  }
}

set<int> solve(const vector<set<int>>& graph) {
  int n = graph.size();
  vector<int> pre(n, -1);
  vector<int> low(n, numeric_limits<int>::max());
  set<int> arts;
  int label = 0;
  for (int u=0;u<n;++u) {
    if (pre[u] == -1) {
      dfs(graph, pre, low, label, -1, u, arts);
    }
  }
  return arts;
}

int main() {
  int N, R;
  int cases = 1;
  while (cin >> N) {
    if (N==0) break;
    map<string, int> cities;
    vector<string> inv_cities;
    for (int i=0;i<N;++i) {
      string city;
      cin >> city;
      cities[city] = i;
      inv_cities.push_back(city);
    }
    cin >> R;
    vector<set<int>> graph(N, set<int>());
    for (int i=0;i<R; ++i) {
      string city1, city2;
      cin >> city1 >> city2;
      int from = cities[city1];
      int to = cities[city2];
      graph[from].insert(to);
      graph[to].insert(from);
    }

    if (cases > 1) {
      cout << endl;
    }
    set<int> arts = solve(graph);
    cout << "City map #" << cases << ": " << arts.size() << " camera(s) found" << endl;
    set<string> answer;
    for (int art : arts) {
      answer.insert(inv_cities[art]);
    }
    for (const string& a : answer) {
      cout << a << endl;
    }
    cases++;
  }
}
