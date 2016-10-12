#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>
#include <limits>
using namespace std;

// 2016/10/12
// SKILL: dijkstra
// STAR:
// TRAP:

struct Edge {
  int to;
  int time;
};

int MAX = numeric_limits<int>::max() / 8;

typedef pair<int, int> II;

int solve(vector<vector<Edge>>& graph, int n, int m) {
  // dijkstra
  set<II> heap;
  vector<int> dist(graph.size(), MAX);
  int s = n*m;
  dist[s] = 0;
  heap.insert({0, s});
  while (!heap.empty()) {
    II top = *(heap.begin());
    heap.erase(top);
    int u = top.second;
    int time = top.first;
    if (u!= s && u/m >= n-1) {
      return time;
    }
    for (const Edge& edge : graph[u]) {
      int v = edge.to;
      int n_time = time + edge.time;
      if (n_time < dist[v]) {
        if (dist[v] != MAX) {
          heap.erase({dist[v], v});
        }
        dist[v] = n_time;
        heap.insert({n_time, v});
      }
    }
  }
  return -1;  // should not happen
}

int main() {
  string building;
  while (cin >> building) {
    int n, m;
    cin >> n >> m;
    int s = n*m;

    // each graph[idx][k] towards graph[(idx/m+1)*m + k]
    vector<vector<Edge>> graph(n*m+1, vector<Edge>(m, {0,0}));
    int idx = 0;
    for (int i=0;i<n-1;++i) {
      for (int j=0;j<m;++j) {
        for (int k =0;k<m;++k) {
          int time;
          cin >> time;
          time += 2;
          int to = (i+1)*m + k;
          graph[idx][k] = {to, time};
        }
        idx++;
      }
    }
    for (int i=0;i<m;++i) {
      graph[s][i] = {i, 0};
    }
    cout << building << endl;
    cout << solve(graph, n, m) << endl;
  }
}
