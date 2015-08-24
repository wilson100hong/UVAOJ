// NOTE: We need to use Edmonds-Karp in this question. Ford-Fulkerson is too slow. Yes, it will caused TLE.

#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define CAP_INF 1 << 30
#define NOT_VISIT -1

typedef map<int, map<int, int>> Graph;

int min(int a, int b) {
  return a < b ? a : b;
}

void dump_graph(const Graph& g) {
  for (const auto& kvp : g) {
    cout << kvp.first << ": ";
    for (const auto& edge : kvp.second) {
      cout << "(" << edge.first << "," << edge.second << "), ";
    }
    cout << endl;
  }
}

bool read_input(Graph& g) {
  int N, M, B, D, from, to, cap;
  if (!(cin >> N)) {
    return false;
  }
  // Add source and sink node
  int src = 0, sink = 2 * N + 1;
  g[src] = {};
  g[sink] = {};
  // Add regulators. Each regulator has two nodes
  for (int n = 1; n <= N; ++n) {
    cin >> cap;
    g[n] = {{n + N, cap}};  // regulator in node
    g[n + N] = {{n, cap}};  // regulator out node
  }
  cin >> M;
  for (int m = 0; m < M; ++m) {
    cin >> from >> to >> cap;
    // Add edge for "from" regulator's out node
    g[from + N][to] = cap;
    g[to][from + N] = 0;
  }
  cin >> B >> D;
  // Add edge from source node
  for (int b = 0; b < B; ++b) {
    cin >> to;
    g[src][to] = CAP_INF;
  }
  for (int d = 0; d < D; ++d) {
    cin >> from;
    g[from + N][sink] = CAP_INF;
  }
  return true;
}

int edmond_karp(Graph& capacity) {
  Graph flows;
  for (const auto& kv : capacity) {
    flows[kv.first] = {};
  }

  int sum = 0, src = 0, sink = capacity.size() - 1;
  while (1) {
    vector<int> preds(capacity.size(), NOT_VISIT);
    preds[src] = 0;
    queue<int> q;
    q.push(src);
    // BFS
    while (!q.empty() && preds[sink] == NOT_VISIT) {
      int node = q.front();
      q.pop();
      for (const auto& edge : capacity[node]) {
        int neighbor = edge.first;
        if (preds[neighbor] == NOT_VISIT &&
            capacity[node][neighbor] - (flows[node][neighbor] - flows[neighbor][node]) > 0) {
          preds[neighbor] = node;
          q.push(neighbor);
        }
      }
    }

    if (preds[sink] == NOT_VISIT) {
      break;
    }
    // src -> n1 -> n2 -> n3 -> sink
    // only count limit of residue of n1 -> n2, n2 -> n3
    int delta_flow = CAP_INF;
    int cur = preds[sink];
    while (preds[cur] != src) {
      int pred = preds[cur];
      delta_flow = min(delta_flow, capacity[pred][cur] - (flows[pred][cur] - flows[cur][pred]));
      cur = pred;
    }
    // only update n1 -> n2, n2 -> n3
    cur = preds[sink];
    while (preds[cur] != src) {
      flows[preds[cur]][cur] += delta_flow; 
      cur = preds[cur];
    }
    sum += delta_flow;
  }
  return sum;
}

int main() {
  Graph capacity;
  while (read_input(capacity)) {
    cout << edmond_karp(capacity) << endl;
    capacity.clear();
  }
}
