#include <vector>
#include <map>
#include <iostream>
using namespace std;

typedef vector<vector<int>> matrix;
#define NORMAL 0
#define STICK 1
#define PILLAR 2

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3
#define ORI_SIZE 4

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

#define FORWARD 0
#define TURN_RIGHT 1
#define TURN_LEFT 3

int char2cmd(char c) {
  if (c == 'D') return TURN_RIGHT;
  if (c == 'E') return TURN_LEFT;
  if (c == 'F') return FORWARD;
  cout << "WRONG COMMAND" << endl;
  return -1;
}

int char2cell(char c) {
  if (c == '*') return STICK;
  if (c == '#') return PILLAR;
  return NORMAL;
}

int char2ori(char c) {
  if (c == 'N') return NORTH;
  if (c == 'S') return SOUTH;
  if (c == 'L') return EAST;
  if (c == 'O') return WEST;
  return -1;
}

struct Robot {
  int r;
  int c;
  int o;  // orientation
};

int solve(const vector<int> cmds, matrix& maze, Robot& robot) {
  int N = maze.size();
  int M = maze[0].size();
  int sum = 0;
  for (int cmd : cmds) {
    robot.o = (robot.o + cmd) % ORI_SIZE;
    if (cmd == FORWARD) {
      int nr = robot.r + dr[robot.o];
      int nc = robot.c + dc[robot.o];
      
      if (0 <= nr && nr < N &&
          0 <= nc && nc < M &&
          maze[nr][nc] != PILLAR) {
        if (maze[nr][nc] == STICK) {
          sum++;
          maze[nr][nc] = NORMAL;
        }
        robot.r = nr;
        robot.c = nc;
      }
    }
  }
  return sum;
}

int main() {
  int N, M, S;
  while (cin >> N >> M >> S) {
    if (N == 0 && M == 0 && S == 0) break;
    matrix maze(N, vector<int>(M, NORMAL));
    Robot robot;
    
    for (int n=0;n<N;++n) {
      for (int m=0;m<M;++m) {
        char c;
        cin >> c;
        maze[n][m] = char2cell(c);
        int o = char2ori(c);
        if (o != -1) {
          robot = {n, m, o};
        }
      }
    }
    vector<int> cmds;
    for (int s=0;s<S;++s) {
      char c;
      cin >> c;
      cmds.push_back(char2cmd(c));
    }
    cout << solve(cmds, maze, robot) << endl;
  }
}
