#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#define INF numeric_limits<int>::max()
struct Edge{
  int from;
  int to;
  int cost;
};

bool has_negcycle(const vector<Edge>& edges, vector<int>& dist, int src) {
  //dist.assign(dist.size(), INF);
  dist[src] = 0;

  for (int i = 0; i < dist.size() - 1; ++i) {
    bool update = false;
    for (int j = 0; j < edges.size(); ++j) {
      const Edge& e = edges[j];
      if (dist[e.from] != INF) {
        if (dist[e.from] + e.cost < dist[e.to]) {
          dist[e.to] = dist[e.from] + e.cost;
          update = true;
        }
      }
    }
    if (!update) 
      break;
  }

  // test negative cycle
  for (int j = 0; j < edges.size(); ++j) {
    const Edge& e = edges[j];
    if (dist[e.from] + e.cost < dist[e.to]) {
      return true;
    }
  }
  
  return false;
}

int main () {
  int c, n, m;
  cin >> c;
  while (c-- > 0) {
    cin >> n >> m;
    vector<int> dist(n, INF);
    vector<Edge> edges;
    while (m-- > 0) {
      Edge e;
      cin >> e.from >> e.to >> e.cost;
      edges.push_back(e);
    }
    bool possible =  has_negcycle(edges, dist, 0);
    cout << (possible ? "possible" : "not possible") << endl;
  }
}

