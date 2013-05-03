#include <iostream>
#include <queue>
using namespace std;

void dump(int** ary, int m, int n) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j)
      cout << ary[i][j] << ",";
    cout << endl;
  }
}

int dr[] = {1,  1,  1,  0,  0,  -1,  -1, -1};
int dc[] = {-1, 0,  1,  1,  -1,  -1,  0,  1};

void dfs(int** ary, int m, int n, int r, int c, int color) {
  if (0 <= r && r < m && 0 <= c && c < n) {
    int cur = ary[r][c];
    if (cur == 0) {
      // 0 means not color yet   
      ary[r][c] = color;
      for (int i = 0; i < 8; ++i) {
        dfs(ary, m, n, r + dr[i], c + dc[i], color);
      }
    }
  }
}

int main () {
  int m, n;
  string line;
  while (cin >> m >> n) {
    if (m == 0)
      break;
    getline(cin, line);
    int** ary = new int*[m];
    for (int i = 0; i < m; ++i) {
      getline(cin, line);
      ary[i] = new int[n];
      for (int j = 0; j < n; ++j) {
        char c = line[j];
        if (c == '*') {
          ary[i][j] = -1;
        } else if (c == '@') {
          ary[i][j] = 0;
        }
      }
    }
    //dump(ary, m, n);
    int color = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
         if (ary[i][j] == 0) {
            color++;
            dfs(ary, m, n, i, j, color); 
         }
      }
    }
    cout << color << endl;
    // dump(ary, m, n);
  }
  return 0;
}
