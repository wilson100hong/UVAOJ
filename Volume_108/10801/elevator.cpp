#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <utility>

using namespace std;

#define INF std::numeric_limits<int>::max()
#define TRNS 60

vector<map<int, int>> graph;  // node - cost
map<int, int> floor_of_node;

int min(int a, int b) {
  return a < b ? a : b;
}

int abs(int n) {
  return n > 0 ? n : -n;
}

typedef pair<int, int> II;  // dist - node
int dijkstra(int start, int target_floor) {
  set<II> heap;
  heap.insert(make_pair(0, start));
  vector<int> distance(graph.size(), INF);
  distance[start] = 0;

  while (!heap.empty()) {
    II top = *heap.begin();
    heap.erase(top);
    int dist = top.first, node = top.second;
    if (floor_of_node[node] == target_floor) {
      return dist;  // the first touch-down should be shortest. Make sure this is correct
    }

    for (const auto& edge : graph[node]) {
      int next = edge.first;
      int alt = dist + edge.second;
      if (alt < distance[next]) {
        if (distance[next] != INF) {
          II to_be_remove = make_pair(distance[next], next);
          heap.erase(to_be_remove);
        }
        distance[next] = alt;
        heap.insert(make_pair(alt, next));
      }
    }
  }
  return INF;
}

void solve(int target_floor) {
  // try all possible start
}

int main() {
  string line;
  int N, K;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> N >> K;
    getline(cin, line); stringstream ss2(line);

    vector<int> costs;
    for (int n = 0; n < N; ++n) {
      int cost;
      ss2 >> cost;
      costs.push_back(cost);
    }

    // build graph
    graph.clear();
    floor_of_node.clear();
    map<int, set<int>> nodes_at_floor;

    // construct nodes in each elevator.
    for (int n = 0; n < N; ++n) {
      getline(cin, line); stringstream ss3(line);
      int floor;
      int prev = -1;
      while (ss3 >> floor) {
        int node = graph.size();
        graph.push_back(map<int, int>());
        if (nodes_at_floor.count(floor) == 0) {
          nodes_at_floor[floor] = set<int>();
        }
        nodes_at_floor[floor].insert(node);
        floor_of_node[node] = floor;
        if (prev != -1) {
          graph[node][prev] = graph[prev][node] = costs[n] * abs(floor_of_node[node] - floor_of_node[prev]);
        }
        prev = node;
      }
    }

    // connect nodes between different elevator
    for (const auto& kvp : nodes_at_floor) {
      int floor = kvp.first;
      for (int u : kvp.second) {
        for (int v : kvp.second) {
          if (u != v) {
            graph[u][v] = TRNS;
          }
        }
      }
    }

    int ans = INF;
    for (int i = 0; i < graph.size(); ++i) {
      if (floor_of_node[i] == 0) {
        ans = min(ans, dijkstra(i, K));
      }
    }
    if (ans == INF) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
