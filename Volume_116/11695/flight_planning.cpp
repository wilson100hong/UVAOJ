#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

// 2016/10/09
// SKILL: tree diameter, radius (balanced height)
// STAR: ****
// TRAP: very tricky to implement

int max(const vector<int>& v) {
  int res = -1;
  for (int e : v) {
    if (e > res) res = e;
  }
  return res;
}

bool eqp(const pair<int, int>& p, int a, int b) {
  if (p.first == a && p.second == b) return true;
  if (p.second == a && p.first == b) return true;
  return false;
}

struct Result{
  int root;
  int depth;
  int diameter;
};

void update(
    vector<int>& h1, vector<int>& h2,
    vector<int>& c1, vector<int>& c2,
    int u, int v, int height) {
  if (height > h1[u]) {
    h2[u] = h1[u]; c2[u] = c1[u];
    h1[u] = height; c1[u] = v;
  } else if (height > h2[u]) {
    h2[u] = height; c2[u] = v;
  }
}

void dfs1(vector<set<int>>& graph, const pair<int, int>& forbidden,
    vector<int>& h1, vector<int>& h2,
    vector<int>& c1, vector<int>& c2,
    vector<int>& parent, int u) {
  for (int v : graph[u]) {
    if (v != parent[u] && !eqp(forbidden, u, v)) {
      parent[v] = u;
      dfs1(graph, forbidden, h1, h2, c1, c2, parent, v);
      int height = h1[v] + 1;
      update(h1, h2, c1, c2, u, v, height);
    }
  }
}

void dfs2(vector<set<int>>& graph, const pair<int, int>& forbidden,
    vector<int>& h1, vector<int>& h2,
    vector<int>& c1, vector<int>& c2,
    vector<int>& parent, int u) {
  int p = parent[u];
  if (p != u) {
    // only do in non-root nodes
    if (p == -1) {
      // should not happen
      cout << "YOU STUPID" << endl;
    }
    int height;
    if (c1[p] == u) {
      height = 1 + h2[p];
    } else {
      height = 1 + h1[p];
    }
    update(h1, h2, c1, c2, u, p, height);
  }
  for (int v : graph[u]) {
    if (v != p && !eqp(forbidden, u, v)) {
      dfs2(graph, forbidden, h1, h2, c1, c2, parent, v);
    }
  }
}


Result radius(
    vector<set<int>>& graph, int node,
    const pair<int, int>& forbidden) {
  int n = graph.size();
  vector<int> h1(n, 0);
  vector<int> h2(n, 0);
  vector<int> c1(n, -1);
  vector<int> c2(n, -1);
  vector<int> parent(n, -1);

  // 1. dfs1, find all node's subtree height h1 & h2
  parent[node] = node;
  dfs1(graph, forbidden, h1, h2, c1, c2, parent, node);

  // 2. dfs2, find all nodes's height as root 
  
  dfs2(graph, forbidden, h1, h2, c1, c2, parent, node);

  // 3. find root
  int root = -1;
  int depth = n;
  int diameter = 0;
  for (int u=0;u<n;++u) {
    if (parent[u] == -1) continue;  // not traversed in 
    int d = h1[u] + h2[u]; 
    if (d > diameter) {
      diameter = d;
    }
    if (h1[u] < depth) {
      root = u;
      depth = h1[u];
    }
  }
  return {root, depth, diameter};
}

void dumppair(const pair<int, int>& p) {
  // convert to 1-based
  if (p.first < p.second) {
    cout << p.first+1 << " " << p.second+1 << endl;
  } else {
    cout << p.second+1 << " " << p.first+1 << endl;
  }
}

void dump(int n, const pair<int, int>& p1, const pair<int, int>& p2) {
  cout << n << endl;
  dumppair(p1);
  dumppair(p2);
}

// DEBUG
void dump(const Result& res) {
  cout << "root: " << res.root << "  depth: " << res.depth << " diameter: " << res.diameter << endl;
}

void dump(vector<set<int>>& graph) {
  int idx = 0;
  for (const set<int> vs : graph) {
    cout << idx++ << ": ";
    for (int v : vs) {
      cout << " " << v;
    }
    cout << endl;
  }
}

void solve(vector<set<int>>& graph, vector<pair<int, int>>& edges) {
  Result r = radius(graph, 0, {-1, -1});

  int best = r.diameter;

  pair<int, int> erase;
  pair<int, int> added;

  for (const auto& edge : edges) {
    int u = edge.first, v = edge.second;
    Result res1 = radius(graph, u, edge);
    Result res2 = radius(graph, v, edge);
    int longest = max({res1.diameter, res2.diameter, res1.depth + res2.depth + 1});
    if (longest < best) {
      best = longest;
      erase = edge;
      added = {res1.root, res2.root};
    }
  }
  dump(best, erase, added);
}

int main() {
  int N;
  cin >> N;
  while (N--) {
    int n;
    cin >> n;
    // TODO: might need optimize
    vector<set<int>> graph(n, set<int>());
    vector<pair<int, int>> edges;
    for (int i=0;i<n-1;++i) {
      int u, v;
      cin >> u >> v;
      // convert to 0-based
      u--; v--;
      graph[u].insert(v);
      graph[v].insert(u);
      edges.push_back({u, v});
    }

    solve(graph, edges);
  }
}
