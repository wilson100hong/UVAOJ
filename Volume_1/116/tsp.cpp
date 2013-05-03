#include <iostream>
#include <vector>
using namespace std;
#define MAX_ROW 10
#define MAX_COL 100
#define MAX_INT 2147483467 

int weight[MAX_ROW][MAX_COL];
int prev[MAX_ROW][MAX_COL];

int cost[MAX_ROW];
int n_cost[MAX_ROW]; 
int paths[MAX_COL];

void dump(int m, int n, int matrix[][MAX_COL]) {
  for (int row = 0; row < m; ++row) {
    for (int col = 0; col < n; ++col) 
      cout << matrix[row][col] << " ";
    cout << endl;
  }
}

int dr[] = {-1, 0, 1};

bool pathBefore(int c, int or1, int or2) {
  int r1 = or1;
  int r2 = or2;
  while (prev[r1][c] != prev[r2][c]) {
    r1 = prev[r1][c];
    r2 = prev[r2][c];
    if (r1 == MAX_INT || r2 == MAX_INT) {
      cout << c << ", " << or1 << ", " << or2 << endl;
      cout << "WTF" << endl;
    }
    c--;
  }
  return r1 < r2;
}

int main() {
  int m, n;
  while (cin >> m >> n) {
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c)
        cin >> weight[r][c];
      cost[r] = MAX_INT;
    }
    
    for (int r = 0; r < m; ++r) {
      cost[r] = weight[r][0];
    }

    for (int c = 1; c < n; ++c) {
      for (int r = 0; r < m; ++r) {
        n_cost[r] = MAX_INT;
        prev[r][c] = MAX_INT;
      } 
      
      for (int r = 0; r < m; ++r) {
        if (cost[r] != MAX_INT) {
          for (int i = 0; i < 3; ++i) {
            int n_r = (m + r + dr[i]) % m;
            int tmp = cost[r] + weight[n_r][c];
            if (tmp < n_cost[n_r] ||
                (tmp == n_cost[n_r] && pathBefore(c - 1, r, prev[n_r][c]))) {
              n_cost[n_r] = tmp;
              prev[n_r][c] = r;
            } 
          }
        }
      }
      for (int r = 0; r < m; ++r) {
        cost[r] = n_cost[r];
        //cout << "cost: " << cost[r] << endl;
      }
      //cout << endl;
    }
    
    int best = MAX_INT;
    int end_r = -1;
    for (int r = 0; r < m; ++r) {
      if (cost[r] < best ||
          (cost[r] == best && pathBefore(n-1, r, end_r))) {
        best = cost[r];
        end_r = r;
      }
    }
    paths[n - 1] = end_r;
    int col = n -1;
    while (col > 0) {
      paths[col - 1] = prev[end_r][col];
      end_r = prev[end_r][col];
      col--;
    }
    cout << paths[0] + 1;
    for (int c = 1; c < n ; ++c)
      cout << " " << paths[c] + 1;
    cout << endl;
    cout << best << endl;
  }
  return 0;
}
