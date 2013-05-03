#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 20
#define ARB 1.01f

double edges[MAX_N][MAX_N];
double dist[MAX_N][MAX_N][MAX_N + 1];
int prev[MAX_N][MAX_N][MAX_N + 1];

void dump(int n, int curLen) {
  for (int len = 1; len <= curLen; ++len) {
    cout << "Len = " << len << ": " << endl;
    cout << "Dist:" << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) 
        cout << dist[i][j][len] << ", ";
      cout << endl;
    }
    cout << endl << "Prev:" << endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) 
        cout << prev[i][j][len] << ", ";
      cout << endl;
    }
    cout << endl;
  }
}

int main() {
  // 1. read input and initialize
  int n;
  while (cin >> n) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n ; ++j) {
        prev[i][j][1] = i;
        if (i != j) {
          cin >> edges[i][j];
          dist[i][j][1] = edges[i][j];
        } else {
          edges[i][j] = 1;
          dist[i][j][1] = 1;
        }
        for (int len = 2; len <= n; ++len)
          dist[i][j][len] = 0;
      }
    }
    // 2. floyd-warshall
    bool arb = false;
    for (int len = 2; len <= n && arb == false; ++len) {
      for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            if (dist[i][k][len-1] * dist[k][j][1] > dist[i][j][len]) {
              dist[i][j][len] = dist[i][k][len-1]*dist[k][j][1];
              prev[i][j][len] = k;
            }
          }
        }
      }

      // Test arbitrage existence
      for (int i = 0; i < n; ++i) {
        if (dist[i][i][len] > 1.01) {
          //dump(n, len);
          arb = true;
          vector<int> path;
          int point = i;
          for (int l = len; l > 0; --l) { 
            path.push_back(prev[i][point][l] + 1);
            point = prev[i][point][l];
          }
          // cout << "Path: " << endl;
          for (int j = path.size() - 1; j >= 0; --j) 
            cout << path[j] << " ";
          cout << i + 1 << endl;
          break;
        }
      }
    }
    if (arb == false)
      cout << "no arbitrage sequence exists" << endl;
  }
  return 0;
}
