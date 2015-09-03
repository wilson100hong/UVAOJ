#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define UNVISIT -1

struct Rank{
  int node;
  int post;
};
vector<vector<int>> G;  // graph
vector<Rank> P; 

bool compare_rank(const Rank& r1, const Rank& r2) {
  return r1.post > r2.post;
}

int dfs(int node, int post) {
  for (int i = 0; i < G[node].size(); ++i) {
    int next = G[node][i];
    if (P[next].post == UNVISIT) {
      post = dfs(next, post);
    }
  }
  P[node].post = post++;
  return post;
}

void solve() {
  P.clear();
  for (int i = 0; i < G.size(); ++i) {
    P.push_back({i, UNVISIT});
  }
  int post = 0;
  for (int i = 0; i < G.size(); ++i) {
    if (P[i].post == UNVISIT) {
      post = dfs(i, post);
    }
  }

  sort(P.begin(), P.end(), &compare_rank);
  for (int i = 0; i < P.size(); ++i) {
    if (i > 0) cout << " ";
    cout << P[i].node + 1;
  }
  cout << endl;
}

int main() {
  int n, m;
  while (1) {
    cin >> n >> m;
    if (n == 0 && m ==0) break;
    G.clear();
    for (int i = 0; i < n; ++i) {
      G.push_back(vector<int>());
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      u--; v--;
      G[u].push_back(v);
    }
    solve();
  }
}
