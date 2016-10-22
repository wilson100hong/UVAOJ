#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <limits>
using namespace std;

// 2016/10/22
// STAR: *
// SKILL: prim
// TRAP: 1) the entire graph might not be connected
//       2) dist[] could be 0 even not added

// from a node
struct Edge{
  int to;
  int w;
  int e;  // edge index
};

typedef unsigned long long ULL;

ULL MAX = numeric_limits<ULL>::max();
typedef pair<ULL, int> UI;

#define NO_EDGE -1
#define CONNECT 0 

set<int> prims(const vector<vector<Edge>>& graph,
               int start,
               vector<ULL>& dist) {
  set<int> mst;
  set<UI> heap;  // cost - node
  vector<int> by_edge(graph.size(), NO_EDGE);
  by_edge[start] = NO_EDGE;
  heap.insert({0, start});

  while (!heap.empty()) {
    UI top = *heap.begin();
    heap.erase(top);
    int node = top.second;
    dist[node] = CONNECT;
    if (by_edge[node] != NO_EDGE) {
      mst.insert(by_edge[node]);
    }
    for (const Edge& edge : graph[node]) {
      int to = edge.to;
      if (edge.w < dist[to]) {
        if (dist[to] != MAX) {
          heap.erase({dist[to], to});
        }
        dist[to] = edge.w;
        by_edge[to] = edge.e;
        heap.insert({dist[to], to});
      }
    }
  }
  return mst;
}

// return all edges in MSTs
set<int> solve(const vector<vector<Edge>>& graph) {
  set<int> msts;

  int n = graph.size();
  vector<ULL> dist(n, MAX);
  for (int i=0;i<n;++i) {
    if (dist[i] == MAX) {
      set<int> mst = prims(graph, i, dist);
      for (int e : mst) {
        msts.insert(e);
      }
    }
  }
  return msts;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    if (n==0 && m==0) break;
    vector<int> weights;  // store edge's weight
    vector<pair<int, int>>  edges;

    // graph[u] is all the index of edges
    vector<vector<Edge>> graph(n, vector<Edge>());
    for (int i=0;i<m;++i) {
      int u, v, w;
      cin >> u >> v >> w;
      int e = weights.size();
      weights.push_back(w);
      graph[u].push_back({v, w, e});
      graph[v].push_back({u, w, e});
      edges.push_back({u, v});
    }

    set<int> msts= solve(graph); // return used edge index

    vector<bool> used(m, false);
    for (int e : msts) {
      used[e] = true;
    }
    set<int> heavy;
    for (int i=0;i<m;++i) {
      if (!used[i]) {
        heavy.insert(weights[i]);
      }
    }
    if (heavy.size() == 0) {
      cout << "forest" << endl;
    } else {
      bool first = true;
      for (int h : heavy) {
        if (!first) cout << " ";
        first = false;
        cout << h;
      }
      cout << endl;
    }
  }
}
