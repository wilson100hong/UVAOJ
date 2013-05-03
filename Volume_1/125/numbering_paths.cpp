#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_POINTS 30

int dp[MAX_POINTS][MAX_POINTS];
int result[MAX_POINTS][MAX_POINTS];

void Solve(int m) {
  // Floyd-Warshall method
  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < m; ++i) { 
      for (int j = 0; j < m; ++j) { 
        dp[i][j] += dp[i][k] * dp[k][j];
      }
    }
  }

  // copy to result[][]
  for (int i = 0; i < m; ++i) 
    for (int j = 0; j < m; ++j)
      result[i][j] = dp[i][j];

  // Elimniate infinite points
  for (int i = 0; i < m; ++i) {
    if (dp[i][i] > 0) {
      for (int j = 0; j < m; ++j) {
        if (dp[j][i] > 0) {
          for (int k = 0; k < m; ++k) 
            if (dp[i][k] > 0)
              result[j][k] = -1;
          result[j][i] = -1;
        } 
        if (dp[i][j] > 0)
          result[i][j] = -1;
      }
    }
  }
}

int main() {
  int city = 0;
  int n;
  while (cin >> n) {
    for (int i = 0; i < MAX_POINTS; ++i) {
      for (int j = 0; j < MAX_POINTS; ++j) {
        dp[i][j] = 0;
        result[i][j] = 0;
      }
    }
    int u, v;
    int m = -1;
    while (n-- > 0) {
      cin >> u >> v;
      dp[u][v] = 1;
      m = max(m, max(u, v)); 
    }
    m += 1;
    cout << "matrix for city " << city++ << endl;
    Solve(m);
    for (int i = 0; i < m; ++i) {
      bool first = true;
      for (int j = 0; j < m; ++j) {
        if (first) 
          first = false;
        else
          cout << " ";
        cout << result[i][j];
      }
      cout << endl;
    }
  }
}
