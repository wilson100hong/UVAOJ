#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 2016/10/17
// STAR:
// SKILL: BFS
// TRAP:

struct Task {
  int row;
  int col;
  int time;
};

// up, down, left, right
int DR[] = {-1, 1, 0, 0};
int DC[] = {0, 0, -1, 1};

int main() {
  int R, C;
  while (cin >> R >> C) {
    if (R==0 && C==0) break;
    vector<vector<bool>> map(R, vector<bool>(C, true));
    int NR;
    cin >> NR;
    while (NR--) {
      int row, col, nb;
      cin >> row >> nb;
      while (nb--) {
        cin >> col;
        map[row][col] = false;
      }
    }
    int sr, sc, dr, dc;
    cin >> sr >> sc >> dr >> dc;
    // BFS
    queue<Task> que;
    que.push({sr, sc, 0});
    map[sr][sc] = false;
    int ans = 0;
    while(!que.empty()) {
      Task head = que.front();
      que.pop();
      if (head.row == dr && head.col == dc) {
        ans = head.time;
        break;
      }
      for (int d=0;d<4;++d) {
        int nr = head.row + DR[d];
        int nc = head.col + DC[d];
        if (0<=nr&&nr<R && 0<=nc&&nc<C && map[nr][nc]) {
          map[nr][nc] = false;
          que.push({nr, nc, head.time+1});
        }
      }

    }
    cout << ans << endl;
  }
}
