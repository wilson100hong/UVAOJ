#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <map>

using namespace std;

int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};

bool BM(const vector<set<int>>graph, int u, vector<int>& matched, vector<bool>& visited) {
  visited[u] = true;
  for (int v : graph[u]) {
    if (visited[v]) continue;

    visited[v] = true;
    if (matched[v] == -1 ||
        BM(graph, matched[v], matched, visited)) {
      // Success.
      matched[u] = v;
      matched[v] = u;
      return true;
    }
  }
  return false;
}

int Solve(const vector<vector<char>>& grids) {
  const int H = grids.size();
  const int W = grids[0].size();

  // Build bipartite graph.
  vector<vector<int>> indexing(H, vector<int>(W, -1));

  vector<int> left_indices;  // even i+j
  vector<int> right_indices;

  vector<set<int>> graph;
  for (int i=0;i<H;++i) {
    for (int j=0;j<W;++j) {
      if (grids[i][j] != '*') {
        continue;
      }
      int u = graph.size();
      indexing[i][j] = u;
      graph.push_back(set<int>());
      if ((i+j) % 2 == 0) {
        left_indices.push_back(u);
      } else {
        right_indices.push_back(u);
      }
    
    }
  }
  int N = graph.size();

  for (int i=0;i<H;++i) {
    for (int j=0;j<W;++j) {
      if (grids[i][j] != '*') {
        continue;
      }
      int u = indexing[i][j];
      for (int d=0;d<4;++d) {
        int ni = i + di[d], nj = j + dj[d];
        if (0 <= ni && ni < H && 0 <= nj && nj < W
            && grids[ni][nj] == '*') {
          int v = indexing[ni][nj];
          graph[u].insert(v);
        }
      }
    }
  }

  vector<int> matched(N, -1);
  int M = 0;
  for (int u : left_indices) {
    if (matched[u] == -1) {
      vector<bool> visited(N, false);
      if (BM(graph, u, matched, visited)) {
        M++;
      }
    }
  }
  return N - M;
}

int main() {
  int N;
  cin >> N;
  while (N--) {
    int H, W;
    cin >> H >> W;
    vector<vector<char>> grids(H, vector<char>(W, ' '));
    for (int i=0;i<H;++i) {
      for (int j=0;j<W;++j) {
        cin >> grids[i][j];
      }
    }
    cout << Solve(grids) << endl;
  }
}
