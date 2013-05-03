#include <iostream>
#include <vector>

using namespace std;
#define MAX_M 50
#define MAX_N 50

struct Grid{
  bool obstacle;
  int cost;
  int value;
};

int DX[] = {1, 0, -1,  0};
int DY[] = {0, 1,  0, -1};

void Rebounce(int& dir) {
  dir = (dir + 3) % 4;
}

struct Ball{
  int x;
  int y;
  int dir;
  int life;
};

void DumpGame(Grid grids[MAX_M][MAX_N], Ball& ball, int M, int N) {
  for (int j = N - 1; j >= 0; --j) {
    for (int i = 0; i < M; ++i) {
      if (grids[i][j].obstacle) {
        if (grids[i][j].value == 0)
          cout << "W";
        else
          cout << "B";
      } else 
        cout << " ";
    }
    cout << endl;
  }
}

int main() {
  Grid grids[MAX_M][MAX_N];
  for (int i = 0; i < MAX_M; ++i)
    for (int j = 0; j < MAX_N; ++j) {
      grids[i][j].obstacle = false;
      grids[i][j].cost = 0;
      grids[i][j].value = 0;
    }
  int M, N;
  cin >> M >> N;
  int x, y, value, cost;
  cin >> cost;
  // Build walls
  for (int i = 0; i < M; ++i) {
    grids[i][0].obstacle = true; grids[i][0].cost = cost;
    grids[i][N - 1].obstacle = true; grids[i][N - 1].cost = cost;
  }
  for (int j = 0; j < N; ++j) {
    grids[0][j].obstacle = true; grids[0][j].cost = cost;
    grids[M - 1][j].obstacle = true; grids[M - 1][j].cost = cost;
  }
  int P;
  cin >> P;
  // Build bumpers
  while (P-- > 0) {
    cin >> x >> y >> value >> cost;
    x--; y--;
    grids[x][y].obstacle = true;
    grids[x][y].value = value;
    grids[x][y].cost = cost;
  }

  // Start simulation:
  Ball ball;
  int sum = 0;
  int dir, life;
  while (cin >> x >> y >> dir >> life) {
    int score = 0;
    x--; y--;
    ball.x = x; ball.y = y; ball.dir = dir; ball.life = life;
    while (ball.life > 0) {
      // simulation here
      // 1. dec life
      ball.life--;
      if (ball.life <= 0)
        break;   
      // 2. move the ball
      int next_x = ball.x + DX[ball.dir];
      int next_y = ball.y + DY[ball.dir];
      if (!grids[next_x][next_y].obstacle) {
        ball.x = next_x;
        ball.y = next_y;
      } else {
        ball.life -= grids[next_x][next_y].cost;   
        score += grids[next_x][next_y].value;
        Rebounce(ball.dir);
      }
    }
    cout << score << endl;
    sum += score;
  }
  cout << sum << endl;
}
