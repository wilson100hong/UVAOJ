// 2016/10/04
// SKILL: dfs
// STAR: *
// TRAP: i/o, there can be duplicate pairs..
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};

int dfs(const vector<vector<int>>& grids,
    vector<vector<int>>& group,
    int i, int j, int color) {
  int N = grids.size();
  group[i][j] = color;
  int total = 1;
  for (int d=0;d<4;++d) {
    int ni = i + di[d];
    int nj = j + dj[d];
    if (0<= ni && ni < N &&
        0<= nj && nj < N &&
        group[ni][nj] == -1 &&
        grids[ni][nj] == color) {
      total += dfs(grids, group, ni, nj, color);
    }
  }
  return total;
}

void solve(const vector<vector<int>>& grids, int N) {
  // each dfs should return eaxactly N
  vector<vector<int>> group(N, vector<int>(N, -1));
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      if (group[i][j] == -1) {
        int color = grids[i][j];
        int gn = dfs(grids, group, i, j, color);
        if (gn != N) {
          cout << "wrong" << endl;
          return;
        }
      }
    }
  }
  cout << "good" << endl;
}

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}


int main() {
  int N;
  int i, j;
  while (1) {
    eatline() >> N;
    if (N == 0) break;
    vector<vector<int>> grids(N, vector<int>(N, N-1));
    for (int n=0;n<N-1;++n) {
      stringstream& ss = eatline();
      int cnt = 0;
      while (ss >> i >> j) {
        grids[i-1][j-1] = n;
        cnt++;
      }
    }
    solve(grids, N);
  }
}
