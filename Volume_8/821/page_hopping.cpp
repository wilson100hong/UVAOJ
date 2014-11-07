#include <iomanip> 
#include <iostream>
#include <set>

#define MAX 101
#define INF 1 << 30

using namespace std;

int edges[MAX][MAX];
int N;
set<int> nodes;

int max(int a, int b) {
  return a > b ? a : b;
}

void reset() {
  for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j)
      edges[i][j] = INF;
  N = 0;
  nodes.clear();
}

void dump() {
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      if (edges[i][j] == INF) cout << "X";
      else cout << edges[i][j];
    }
    cout << endl;
  }
}

void solve(int round) {
  for (int n = 1; n <= N; ++n) {
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        if (nodes.count(i) != 0 && nodes.count(j) != 0 && 
            edges[i][n] != INF && edges[n][j] != INF &&
            edges[i][n] + edges[n][j] < edges[i][j]) {
          edges[i][j] = edges[i][n] + edges[n][j];
        }
      }
    }
  }
  int sum = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      if (nodes.count(i) != 0 && nodes.count(j) != 0)
        sum += edges[i][j];
  int num = nodes.size() * (nodes.size() - 1);
  float ans = (float) sum / num;

  // format: Case 1: average length between pages = 1.833 clicks
  cout << "Case " << round << ": average length between pages = ";
  cout << fixed << setprecision(3) << ans;
  cout << " clicks" << endl;
}

int main() {
  reset();
  // read input
  int u, v;
  bool in_question = false;
  int round = 1;
  while (1) {
    cin >> u >> v;
    if (u == 0 && v == 0) {
      if (!in_question) break;
      in_question = false;
      // set diagonal to 0
      for (int i = 1; i <= N; ++i) {
        if (nodes.count(i) != 0)
          edges[i][i] = 0;
      }
      solve(round++);
      reset();
    } else {
      in_question = true;
      edges[u][v] = 1;
      nodes.insert(u);
      nodes.insert(v);
      N = max(N, max(u, v));
    }
  }
}
