#include <iostream>
#include <vector>

using namespace std;

#define MAX_FLOW 1001
#define MAX_N 101

int N;  // number of nodes
int C[MAX_N][MAX_N];  // capacity
int F[MAX_N][MAX_N];  // flow
bool V[MAX_N];  // visited array

int min(int a, int b) {
  return a < b ? a : b;
}

bool find(int node, int t, int* flow, vector<int>& path) {
  path.push_back(node);
  V[node] = true;

  if (node == t) {
    return true;
  }

  for (int next = 1; next <= N; ++next) {
    int residue = C[node][next] - F[node][next];
    if (!V[next] && residue > 0) {
      int new_flow = min(*flow, residue);
      if (find(next, t, &new_flow, path)) {
        *flow = new_flow;
        return true;
      }
    }
  }
  path.pop_back();
  return false;
}

void update(vector<int>& path, int flow) {
  for (int i = 0; i < path.size() - 1; ++i) {
    int u = path[i], v = path[i + 1];
    F[u][v] += flow;
    F[v][u] = -F[u][v];
  }
}

int max_flow(int s, int t) {
  int sum = 0, flow = MAX_FLOW;
  vector<int> path;
  while (find(s, t, &flow, path)) {
    for (int i = 1; i <= N; ++i)  
      V[i] = false;

    update(path, flow);
    sum += flow;

    flow = MAX_FLOW;
    path.clear();
  }
  return sum;
}

int main() {
  int s, t, e;  // source, sink, number of nodes, number of edges
  int round = 1;
  while (cin >> N) {
    if (N == 0)
      break;

    // read inputs
    cin >> s >> t >> e;

    // init global vars
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        C[i][j] = 0;
        F[i][j] = 0;
      }
      V[i] = false;
    }

    while (e-- > 0) {
      int u, v, c;
      cin >> u >> v >> c;
      C[u][v] += c;
      C[v][u] = C[u][v];
    }

    cout << "Network " << round++ << endl;
    cout << "The bandwidth is " << max_flow(s, t) << "." << endl << endl;
  }
}
