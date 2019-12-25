#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <iomanip>
#include <limits>
#include <tuple>

using namespace std;

typedef pair<int, int> NodeGas;
constexpr int kInf = numeric_limits<int>::max() >> 2;

struct State{
  int node;
  int cost;
  int gas;
};

int Solve(const vector<map<int, int>>& graph, const vector<int>& prices,
    int c, int s, int e) {
  const int N = graph.size();

  set<pair<int, NodeGas>> pq;
  pq.insert({0, {s, 0}});

  // Cost of (node, gas)
  vector<vector<int>> costs(N, vector<int>(c+1, kInf));
  costs[s][0] = 0;

  while (!pq.empty()) {
    auto it = pq.begin();
    const int cost = it->first;
    const int node = it->second.first;
    const int gas = it->second.second;
    pq.erase(it);

    if (node == e) {
      return cost;
    }

    // Iterate all adjacent states.
    vector<State> states;
    // 1. Add 1 gas.
    if (gas < c) {
      states.push_back({node, cost + prices[node], gas + 1});
    }
    // 2. Move to other nodes.
    for (const auto& edge : graph[node]) {
      int next = edge.first;
      int dist = edge.second;
      if (gas >= dist) {
        states.push_back({next, cost, gas - dist});
      }
    }

    for (const auto& state : states) {
      int sn = state.node, sc = state.cost, sg = state.gas;
      if (sc < costs[sn][sg]) {
        if (costs[sn][sg] != kInf) {
          // Update priority queue.
          pq.erase({costs[sn][sg], {sn, sg}});
        }
        costs[sn][sg] = sc;
        pq.insert({sc, {sn, sg}});
      }
    }
  }

  return -1;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> prices(N, -1);
  for (int i=0;i<N;++i) {
    cin >> prices[i];
  }
  vector<map<int, int>> graph(N, map<int, int>());
  for (int i=0;i<M;++i) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u][v] = d;
    graph[v][u] = d;  // Undirectional.
  }
  int Q;
  cin >> Q;
  for (int i=0;i<Q;++i) {
    int c, s, e;
    cin >> c >> s >> e;
    int ans = Solve(graph, prices, c, s, e);
    if (ans < 0) {
      cout << "impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
