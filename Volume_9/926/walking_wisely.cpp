#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <sstream>

// 2016/10/13
// STAR:
// SKILL: dp
// TRAP: 1) coordinate 
//       2) int overflow
using namespace std;

struct Point {
  int x;
  int y;
};

// N, E, S, W
// 0, 1, 2, 3
int dir(char c) {
  if (c=='N') return 0;
  if (c=='E') return 1;
  if (c=='S') return 2;
  if (c=='W') return 3;
}

int DY[] = {1, 0, -1, 0};
int DX[] = {0, 1, 0, -1};

typedef unsigned long long int ULL;
int main() {
  int C, N, W, x, y;
  char D;
  cin >> C;
  while (C--) {
    cin >> N;
    Point sp, ep;
    cin >> x >> y;
    sp = {x-1, y-1};
    cin >> x >> y;
    ep = {x-1, y-1};

    // [y][x]
    vector<vector<ULL>> dp(N, vector<ULL>(N, 0));
    vector<vector<set<int>>> blocks(N, vector<set<int>>(N, set<int>()));
    cin >> W;
    while (W--) {
      cin >> x >> y >> D;
      x--; y--;
      int d = dir(D);
      if (d < 2) {
        // N, E
        blocks[y][x].insert(d);
      } else {
        // S->N, W->E
        int nx, ny;
        nx = x + DX[d];
        ny = y + DY[d];
        blocks[ny][nx].insert(d-2);
      }
    }

    // do dp
    dp[sp.y][sp.x] = 1;
    for (int y=sp.y;y<=ep.y;++y) {
      for (int x=sp.x;x<=ep.x;++x) {
        for (int d=0;d<2;++d) {  // only N, E
          if (!blocks[y][x].count(d)) {
            int nx, ny;
            nx = x + DX[d];
            ny = y + DY[d];
            if (ny < N && nx < N) {
              dp[ny][nx] += dp[y][x];
            }
          }
        }
      }
    }
    cout << dp[ep.y][ep.x] << endl;
  }
}
