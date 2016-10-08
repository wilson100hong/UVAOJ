// 2016/10/07
// STAR: *
// SKILL: SCC
// TRAP: you always make mistake in SCC:
//       1) coloring wrong
//       2) topological sort result sorting
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <utility>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

#define NO_VISIT -2
#define VISIT -1

void dfs1(map<int, set<int>>& graph, int u, int& label, vector<int>& post) {
  post[u] = VISIT;
  for (int v : graph[u]) {
    if (post[v] == NO_VISIT) {
      dfs1(graph, v, label, post);
    }
  }
  post[u] = label++;
}

void dfs2(map<int, set<int>>& graph, int u, int color, vector<int>& group) {
  group[u] = color;
  for (int v : graph[u]) {
    if (group[v] == NO_VISIT) {
      dfs2(graph, v, color, group);
    }
  }
}

int solve(map<int, set<int>>& graph) {
  int n = graph.size();
  // 1. reverse graph
  map<int, set<int>> rev_graph;;
  for (int u=0;u<n;++u) {
    rev_graph[u] = set<int>();
  }
  for (const auto& kv : graph) {
    int from = kv.first;
    for (int to : kv.second) {
      rev_graph[to].insert(from);
    }
  }

  // 2. dfs on reverse graph
  vector<int> post(n, NO_VISIT);
  int label = 0;
  for (int u=0;u<n;++u) {
    if (post[u] == NO_VISIT) {
      dfs1(rev_graph, u, label, post);
    }
  }
  // 3. sort post
  set<pair<int, int>> sorted;
  for (int u=0;u<n;++u) {
    sorted.insert({post[u], u});
  }
  
  // 4. dfs on graph
  vector<int> group(n, NO_VISIT);
  int color = 0;
  for (auto it=sorted.rbegin(); it!=sorted.rend(); ++it) {
    int u = it->second;
    if (group[u] == NO_VISIT) {
      dfs2(graph, u, color, group);
      color++;
    }
  }
  return color;
}

int main() {
  int P, T;
  while (1) {
    eatline() >> P >> T;
    if (P==0 && T==0) break;
    map<string, int> name2id;
    map<int, set<int>> graph;
    for (int i=0;i<P;++i) {
      string name;
      getline(cin, name);
      name2id[name] = i;
      graph[i] = set<int>();
    }
    
    for (int i=0;i<T;++i) {
      string truster, trusted;
      getline(cin, truster); 
      getline(cin, trusted);
      int from = name2id[truster];
      int to = name2id[trusted];
      graph[from].insert(to);
    }
    cout << solve(graph) << endl;
  }
}
