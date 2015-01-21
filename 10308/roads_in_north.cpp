#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define MIN_NODE 1

typedef map<int, int> IntMap;
typedef pair<int, int> IntPair;
typedef map<int, IntMap> Graph;

Graph G;
IntMap D;  // dist

// return the farest node
void dfs(int node, int accum) {
  D[node] = accum;
  for (const auto& v_e: G[node]) {
    if (D.count(v_e.first) == 0) {
      dfs(v_e.first, accum + v_e.second);
    }
  }
}

// return (farest_node, farest_dist)
IntPair farest(int node) {
  D.clear();
  dfs(node, 0); 
  int far_node = MIN_NODE, far_dist = D[far_node];
  for (const auto& v_d : D) {
    if (v_d.second > far_dist) {
      far_node = v_d.first;
      far_dist = v_d.second;
    }
  }
  return IntPair(far_node, far_dist);
}

int solve() {
  IntPair p1 = farest(MIN_NODE);
  IntPair p2 = farest(p1.first);
  return p2.second;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "") {
      cout << solve() << endl;
      G.clear();
    } else {
      // read input
      stringstream ss(line);
      int u, v, cost;
      ss >> u >> v >> cost;
      if (G.count(u) == 0) {
        G[u] = IntMap();
      }
      if (G.count(v) == 0) {
        G[v] = IntMap();
      }
      G[u][v] = cost;
      G[v][u] = cost;
    }
  }
  if (G.size() > 0) {
    cout << solve() << endl;
  }
}
