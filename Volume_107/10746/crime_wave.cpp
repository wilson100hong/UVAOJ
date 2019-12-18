// 1. Use SPAF for min-cost max-flow
// 2. Add EPS to result (WTF!)
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

constexpr double kEps = 1e-10;
constexpr double kInf = numeric_limits<double>::max() / 8.0;

struct Edge {
  int cap; 
  int flow;
  double cost;
};

int SPAF(vector<vector<Edge>>& graph, int m, int n, vector<int>* path) {
  int z = graph.size();
  queue<int> Q;
  vector<bool> inq(z, false);
  vector<double> dist(z, kInf);
  vector<int> last(z, -1);
  vector<int> flow(z, 0);

  Q.push(0);
  inq[0] = true;
  dist[0] = 0;
  last[0] = 0;
  flow[0] = z;

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    inq[u] = false;
    for (int v=0;v<z;++v) {
      if (v == u) continue;
      if (dist[u] < kInf && graph[u][v].cap > graph[u][v].flow) {  // has edge
        if (dist[v] > dist[u] + graph[u][v].cost + kEps) {
          dist[v] = dist[u] + graph[u][v].cost;
          last[v] = u;
          flow[v] = min(flow[u], graph[u][v].cap - graph[u][v].flow);
          if (!inq[v]) {
            Q.push(v);
            inq[v] = true;
          }
        }
      }
    }
  }

  if (flow[1] > 0) {
    int t = 1;
    while (t != 0) {
      path->push_back(t);
      t = last[t];
    }
    path->push_back(0);
  }
  return flow[1];
}

double solve(vector<vector<Edge>>& graph, int m, int n) {
  vector<int> path;

  while (1) {
    const int flow = SPAF(graph, m, n, &path);
    if (flow == 0) break;

    for (int i=0;i<path.size()-1;++i) {
      const int v = path[i];
      const int u = path[i+1];
      graph[u][v].flow += flow;
      graph[v][u].flow -= flow;
    }
    path.clear();
  }

  double cost = 0;
  for (int u=2;u<2+m;++u) {
    for (int v=2+m;v<2+m+n;++v) {
      if (graph[u][v].flow > 0) {
        cost += graph[u][v].flow * graph[u][v].cost;
      }
    }
  }

  return cost / n;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    const int z = n + m + 2;
    vector<vector<Edge>> graph(z, vector<Edge>(z, {0, 0, 0}));

    // src -> courier
    for (int i=2;i<2+m;++i) {
      graph[0][i] = {1, 0, 0};
    }
    // bank -> dst
    for (int i=2+m;i<2+m+n;++i) {
      graph[i][1] = {1, 0, 0};
    }

    for (int v=2+m;v<2+m+n;++v) {
      for (int u=2;u<2+m;++u) {
        cin >> graph[u][v].cost;
        graph[v][u].cost = -graph[u][v].cost;
        graph[u][v].cap = 1;
      }
    }
    cout << fixed << setprecision(2) << solve(graph, m, n) + kEps << endl;
  }
}
