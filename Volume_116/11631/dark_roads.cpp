#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <unordered_set>
#include <limits>
using namespace std;

// 2016/10/22
// STAR:
// SKILL: prims,
// TRAP: 1) return maximum "save"
//       2) use unsigned int for MAX
struct Edge {
  int to;
  int cost;
};

typedef unsigned int UL;

UL MAX = numeric_limits<UL>::max();

typedef pair<UL, int> UI;  

int prim(const vector<vector<Edge>>& graph) {
  int n = graph.size();
  // cost==0: connected, otherwise pending
  vector<UL> cost(n, MAX);
  set<UI> heap;  // cost-node
  heap.insert({0, 0});
  UL total = 0;
  int cnt = 0;

  while (!heap.empty()) {
    UI top = *heap.begin();
    int node = top.second;
    total += top.first;
    heap.erase(top);
    cnt++;
    if (cnt == n) break;
    cost[node] = 0;  // connected
    for (const Edge& edge : graph[node]) {
      if (edge.cost < cost[edge.to]) {
        if (cost[edge.to] != MAX) {
          heap.erase({cost[edge.to], edge.to});
        }
        cost[edge.to] = edge.cost;
        heap.insert({edge.cost, edge.to});
      }
    }
  }
  return total;
}


int main() {
  int m, n, x, y, z;
  while (cin >> m >> n) {
    if (m==0&&n==0) break;
    vector<vector<Edge>> graph(m, vector<Edge>());
    int orig_cost = 0;
    for (int i=0;i<n;++i) {
      cin >> x >> y >> z;
      graph[x].push_back({y, z});
      graph[y].push_back({x, z});
      orig_cost += z;
    }
    int after_cost = prim(graph);
    cout << orig_cost - after_cost << endl;
    
  }
}
