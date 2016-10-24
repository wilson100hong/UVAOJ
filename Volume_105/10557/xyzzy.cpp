#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <queue>
using namespace std;

// 2016/10/23
// STAR: ***
// SKILL: bellmon-ford, constraint
// TRAP: 1) need to disable all relax for nodes with dist[] >= 100
//       2) reachability check from nodes on negative cycles

struct Edge {
  int from;
  int to;
  int cost;  // -1 * energy
};

bool is_reachable(const vector<vector<int>>& graph, const set<int> cycle_nodes) {
  int n = graph.size();
  vector<bool> visit(n, false);
  for (int node : cycle_nodes) {
    if (visit[node]) continue;
    visit[node] = true;
    queue<int> que;
    que.push(node);
    while (!que.empty()) {
      int cur = que.front();
      que.pop();
      for (int next : graph[cur]) {
        if (!visit[next]) {
          visit[next] = true;
          que.push(next);
        }
      }
    }
  }
  return visit[n-1];
}

int MAX = 1e8;

int main() {
  int n;
  while (cin >> n) {
    if (n==-1) break;

    vector<Edge> edges;
    vector<vector<int>> graph(n, vector<int>());
    vector<int> rooms; // energy
    for (int i=0;i<n;++i) {
      int e, nd;
      cin >> e >> nd;
      rooms.push_back(e);
      for (int j=0;j<nd;++j) {
        int v;
        cin >> v;
        edges.push_back({i, v-1, 0});  // 0-based
        graph[i].push_back(v-1);
      }
    }
    // update edges
    for (Edge& edge : edges) {
      edge.cost = -1* rooms[edge.to];
    }
    // bellmon-ford.
    // We disable all paths which at any intermediate point its life <= 0
    vector<int> dist(n, MAX);
    dist[0] = 0;

    for (int i=0;i<n-1;++i) {
      for (const Edge& edge : edges) {
        if (dist[edge.from] >= 100) continue;
        int nd = dist[edge.from] + edge.cost;
        if (nd < 100 && nd < dist[edge.to]) {
          dist[edge.to] = nd;
        }
      }
    }

    // find negative cycle
    set<int> cycle_nodes;
    for (const Edge& edge : edges) {
      if (dist[edge.from] >= 100) continue;
      int nd = dist[edge.from] + edge.cost;
      if (nd < 100 && nd < dist[edge.to]) {
        cycle_nodes.insert(edge.to);
      }
    }
    if (dist[n-1] < 100 || (is_reachable(graph, cycle_nodes) && cycle_nodes.size() > 0)) {
      cout << "winnable" << endl;
    } else {
      cout << "hopeless" << endl;
    }
  }
}
