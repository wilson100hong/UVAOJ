#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

// 2016/10/19
// STAR:
// SKILL: BFS
// TRAP: 1) use static array instead of vector<vector>> to speed up

int SAFE = 1e6;

struct Pos {
  int r;
  int c;
};

struct State {
  int time;
  Pos pos;
};

int DR[] = {1, -1, 0, 0};
int DC[] = {0, 0, 1, -1};

int MAZE[1000][1000];

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int R, C;
    cin >> R >> C;
    // maze[i][j] = k means it becomes impossible at round k
    memset(MAZE, SAFE, sizeof(int)*1000*1000);
    Pos joe;
    vector<Pos> fires;
    for (int i=0;i<R;++i) {
      for (int j=0;j<C;++j) {
        char cell;
        cin >> cell;
        if (cell == '#') {
          MAZE[i][j] = 0; 
        } else if (cell == 'J') {
          joe = {i, j};
        } else if (cell == 'F') {
          fires.push_back({i, j});
          MAZE[i][j] = 0;
        }
      }
    }
    // 1. simulate fires
    queue<State> que;
    for (const Pos& fire : fires) {
      que.push({0, fire});
    }
    while (!que.empty()) {
      State head = que.front();
      que.pop();
      for (int d=0;d<4;++d) {
        int nr = head.pos.r + DR[d];
        int nc = head.pos.c + DC[d];
        if (0<=nr && nr<R && 0<=nc && nc<C
            && head.time+1 < MAZE[nr][nc]) {
          MAZE[nr][nc] = head.time + 1;
          que.push({MAZE[nr][nc], {nr, nc}});
        }
      }
    }
    // 2. joe's move
    que.push({0, joe});
    int et = -1;
    while (!que.empty()) {
      State head = que.front();
      que.pop();
      Pos joe = head.pos;
      // escape ?
      if (joe.r==0 || joe.r==R-1 || joe.c==0 || joe.c==C-1) {
        et = head.time;
        break;
      }

      for (int d=0;d<4;++d) {
        int nr = joe.r + DR[d];
        int nc = joe.c + DC[d];
        if (0<=nr && nr<R && 0<=nc && nc<C
            && head.time+1 < MAZE[nr][nc]) {
          MAZE[nr][nc] = head.time + 1;
          que.push({MAZE[nr][nc], {nr, nc}});
        }
      }
    }

    if (et >= 0) {
      cout << et+1 << endl;  // 1-based
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }
}
