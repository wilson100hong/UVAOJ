// watch out that M is for X, and Y is for N, but input is M lines of N chars.
#include <iostream>
#include <sstream>

using namespace std;

#define MAX_M 20
#define MAX_N 20

int dx[] = {-1, 0, 1, 0};
int dy[] = { 0, 1, 0, -1};
char WORLD[MAX_N][MAX_M];
int M, N;
char LAND, WATER;

stringstream get_ss() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  return ss;
}

int dfs(int x, int y) {
  if (WORLD[y][x] != LAND) {
    return 0;
  }
  WORLD[y][x] = WATER;
  int reward = 1;
  for (int i = 0; i < 4; ++i) {
    int n_y = (y + dy[i] + N) % N;
    int n_x = x + dx[i];
    if (0 <= n_x && n_x < M) {
      reward += dfs(n_x, n_y);
    }
  }
  return reward;
}

char get_water() {
  for (int y = 0; y < N; ++y)
    for (int x = 0; x < M; ++x)
      if (WORLD[y][x] != LAND)
        return WORLD[y][x];
  return LAND+1;  // should not happen
}

int max(int a, int b) {
  return a > b ? a : b;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> M >> N;
    for (int x = 0; x < M; ++x) {
      getline(cin, line);
      for (int y = 0; y < N; ++y) {
        WORLD[y][x] = line[y];
      }
    }
    // decide WATER and LAND
    ss = get_ss();
    int x, y; 
    ss >> x >> y;
    get_ss();  // eat blank line
    LAND = WORLD[y][x];
    WATER = get_water();

    int kingdom = dfs(x, y);  // mark kingdom as WATER
    int colony = 0;
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < M; ++x) {
        colony = max(colony, dfs(x, y));
      }
    }
    cout << colony << endl;
  }
}
