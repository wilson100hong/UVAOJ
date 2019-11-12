#include <iostream>
#include <vector>
using namespace std;

constexpr char kHit = '@';
constexpr char kBody = 'x';
constexpr char kEmpty = '.';
constexpr char kVisit = '#';

// up, right, down, left
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void dfs(vector<vector<char>>& grids, int i, int j) {
  int N = grids.size();
  if (grids[i][j] == kEmpty || grids[i][j] == kVisit) return;
  grids[i][j] = kVisit;
  for (int d=0;d<4;++d) {
    int ni = i + dr[d];
    int nj = j + dc[d];
    if (0 <= ni && ni < N &&
        0 <= nj && nj < N &&
        (grids[ni][nj] == kBody || grids[ni][nj] == kHit)) {
      dfs(grids, ni, nj);
    }
  }
}

int solve(vector<vector<char>>& grids) {
  int N = grids.size();
  int alive = 0;
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      if (grids[i][j] == kBody) {
        alive++;
        dfs(grids, i, j);
      }
    }
  }
  return alive;
}

int main() {
  int T;
  cin >> T;
  for (int t=1;t<=T;++t) {
    int N;
    cin >> N;
    vector<vector<char>> grids(N, vector<char>(N, ' '));
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        char c;
        cin >> c;
        grids[i][j] = c;
      }
    }
    cout << "Case " << t << ": " << solve(grids) << endl;
  }
}
