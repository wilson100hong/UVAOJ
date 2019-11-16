#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

void dfs(const map<string, set<string>>& graph, const string& u, set<string>& visit, vector<string>& post) {
  visit.insert(u);
  for (const string& v : graph.at(u)) {
    if (!visit.count(v)) {
      dfs(graph, v, visit, post);
    }
  }
  post.push_back(u);
}

void solve(const map<string, set<string>>& graph) {
  // SCC
  vector<string> post;
  set<string> visit;
  for (const auto& kv : graph) {
    const string& u = kv.first;
    if (!visit.count(u)) {
      dfs(graph, u, visit, post);
    }
  }

  // Build reverse graph
  map<string, set<string>> rev_graph;
  for (const auto& kv : graph) {
    const string& u = kv.first;
    if (!rev_graph.count(u)) {
      rev_graph[u] = set<string>();
    }
    for (const string& v : kv.second) {
      if (!rev_graph.count(v)) {
        rev_graph[v] = set<string>();
      }
      rev_graph[v].insert(u);
    }
  }

  visit.clear();
  for (int i=post.size()-1;i>=0;--i) {
    const string& u = post[i];
    if (!visit.count(u)) {
      vector<string> group;
      dfs(rev_graph, u, visit, group);
      int first = true;
      for (const string& x : group) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
      }
      cout << endl;
    }
  }
}

int main() {
  int n, m;
  int T = 1;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    map<string, set<string>> graph;
    for (int i=0;i<m;++i) {
      string u, v;
      cin >> u >> v;
      if (!graph.count(u)) {
        graph[u] = set<string>();
      }
      if (!graph.count(v)) {
        graph[v] = set<string>();
      }
      graph[u].insert(v);
    }
    if (T > 1) cout << endl;
    cout << "Calling circles for data set " << T++ << ":" << endl;
    solve(graph);
  }
}
