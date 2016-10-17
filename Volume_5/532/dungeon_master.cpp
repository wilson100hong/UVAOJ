#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// 2016/10/16
// STAR:
// SKILL:
// TRAP:

struct Cell {
  int l;
  int r;
  int c;
};

struct Bucket {
  int cost;
  Cell cell;
};

bool eq(const Cell& c1, const Cell& c2) {
  return c1.l == c2.l && c1.r == c2.r && c1.c == c2.c;
}

// up, down, front, N, S, E, W
int DL[] = {1, -1, 0, 0, 0, 0};
int DR[] = {0, 0, -1, 1, 0, 0};
int DC[] = {0, 0, 0, 0, 1, -1};


int main() {
  int L, R, C;
  while (cin >> L >> R >> C) {
    if (L==0&&R==0&&C==0) break;
    vector<vector<vector<bool>>> dungeon(L, vector<vector<bool>>(R, vector<bool>(C, true)));
    vector<vector<vector<bool>>> visit(L, vector<vector<bool>>(R, vector<bool>(C, false)));

    Cell start, end;
    for (int l=0;l<L;++l) {
      for (int r=0;r<R;++r) {
        for (int c=0;c<C;++c) {
          char x;
          cin >> x;
          if (x=='S') {
            start = {l, r, c};
          } else if(x=='E') {
            end = {l, r, c};
          } else if (x=='#') {
            dungeon[l][r][c] = false;
          }
        }
      }
    }

    // BFS
    bool escape = false;
    queue<Bucket> Q;
    visit[start.l][start.r][start.c] = true;
    Q.push({0, start});

    while (!Q.empty()) {
      Bucket head = Q.front();
      Q.pop();
      Cell cell = head.cell;
      if (eq(cell, end)) {
        cout << "Escaped in " << head.cost << " minute(s)." << endl;
        escape = true;
        break;
      }
      for (int d=0;d<6;++d) {
        int nl = cell.l+DL[d];
        int nr = cell.r+DR[d];
        int nc = cell.c+DC[d];
        if ( 0<=nl && nl<L && 0<=nr && nr<R && 0<=nc && nc<C &&
            dungeon[nl][nr][nc] && !visit[nl][nr][nc]) {
          visit[nl][nr][nc] = true;
          Q.push({head.cost+1, {nl, nr, nc}});
        }
      }
    }
    if (!escape) {
      cout << "Trapped!" << endl;
    }
  }
}
