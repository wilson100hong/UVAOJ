#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
using namespace std;

typedef long long int LL;
LL INF = std::numeric_limits<LL>::max();

struct Edge {
  int to;
  int rev;  // reverse edge is graph[to][rev]
  LL cost;
  LL cap;
  LL flow;
};

int N, M, D, K;
vector<vector<Edge>> graph;

LL min(LL a, LL b) {
  return a < b ? a : b;
}

void add_edge(int u, int v, int cost) {
  graph[u].push_back({v, static_cast<int>(graph[v].size()),     cost, 0, 0});
  graph[v].push_back({u, static_cast<int>(graph[u].size() - 1), cost, 0, 0});
}

void solve(int data) {
  while (data > 0) {
    // 1. Bellmon-Ford to find shortest path
    vector<LL> distance(N, INF);
    vector<int> prev_node(N, -1);
    vector<int> prev_edge(N, -1);
    distance[0] = 0;
    bool update = true;
    while (update) {
      update = false;
      // for all edges
      for (int from = 0; from < N; ++from) {
        for (int i = 0; i < graph[from].size(); ++i) {
          const Edge& edge = graph[from][i];
          if (edge.cap <= 0) continue;  // skip edge already full
          int to = edge.to;
          LL cost = edge.cap <= K ? edge.cost : -1 * edge.cost;
          if (distance[from] != INF && distance[from] + cost < distance[to]) {
            distance[to] = distance[from] + cost;
            prev_node[to] = from;
            prev_edge[to] = i;
            update = true;
          }
        }
      }
    }
    if (distance[N - 1] == INF) {
      cout << "Impossible." << endl;
      return;
    }
    
    // 2. calculate flow on shortest path
    int flow = data;
    for (int node = N - 1; node != 0; node = prev_node[node]) {  // BUG: infinite loop!!
      path.push_back(node);
      LL real_cap = graph[prev_node[node]][prev_edge[node]].cap;
      // if cap > K, it means in has compensate flow (which is -1*cost), to
      // simplify the flow calculation, we only use the compesate caacity part.
      if (real_cap > K) {
        real_cap -= K;
      }
      flow = min(flow, graph[prev_node[node]][prev_edge[node]].cap);
    }

    // 3. update edges on the flow
    for (int node = N - 1; node != 0; node = prev_node[node]) {
      Edge& e1 = graph[prev_node[node]][prev_edge[node]];
      Edge& e2 = graph[node][e1.rev];
      bool is_compensate = e1.cap > K;
      e1.cap -= flow;
      e2.cap += flow;

      if (is_compensate) {
        e2.flow -= flow;
      } else {
        e1.flow += flow;
      }
    }
    data -= flow;
  }
  
  LL sum = 0;
  for (int from = 0; from < N; ++from) {
    for (int i = 0; i < graph[from].size(); ++i) {
      if (graph[from][i].flow < 0) {
        cout << "WILSON IS ASSHOLE" << endl;
      }
      sum += (graph[from][i].flow * graph[from][i].cost);
    }
  }
  cout << sum << endl;
}

int main() {
  string line;
  while (getline(cin, line)) {
    graph.clear();
    stringstream ss(line);
    ss >> N >> M;
    graph.assign(N, vector<Edge>());

    for (int m = 0; m < M; ++m) {
      getline(cin, line);
      stringstream ss2(line);
      int u, v, cost;
      ss2 >> u >> v >> cost;
      u--; v--;  // 0-based index
      add_edge(u, v, cost);
    }
    getline(cin, line);
    stringstream ss3(line);
    ss3 >> D >> K;

    for (auto& edges : graph)
      for (auto& edge : edges)
        edge.cap = K;

    solve(D);
  }
}
