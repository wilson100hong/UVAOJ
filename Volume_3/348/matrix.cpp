#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

#define MAX_N 10
#define INF  std::numeric_limits<unsigned long long>::max()
typedef unsigned long long ULL;

// cost[i][j] is the optimal cost of m[i]*m[i+1]*..*m[j]
ULL cost[MAX_N][MAX_N];

// cut[i][j] describes how to achieve cost[i][j], by separating multiplications into two groups.
// for example, cut[2][6] = 4 means (m[2]*m[3]*m[4]) * (m[5]*m[6])
int cut[MAX_N][MAX_N];

void clear() {
  for (int i = 0; i < MAX_N; ++i) {
    for (int j = 0; j < MAX_N; ++j) {
      cost[i][j] = 0;
      cut[i][j] = -1;
    }
  }
}

string rec(int i, int j) {
  if (i == j) {
    return "A" + std::to_string(i + 1);
  } 
  // i != j
  string left = rec(i, cut[i][j]);
  string right = rec(cut[i][j] + 1, j);
  return "(" + left + " x " + right + ")";
}

void solve(const vector<pair<int, int>>& m) {
  clear();
  int n = m.size();
  // cost[i][j] = min(cost[i][k] + cost[k+1][j] + (m[i].row*m[j].col*m[k].col),  i <= k < j)
  // cost[i][i] = 0; 

  for (int diff = 1; diff < n; ++diff) {
   for (int i = 0, j = i + diff; j < n; ++i, ++j) {
      int best_cut = -1;
      ULL best_cost = INF;
      for (int k = i; k < j; ++k) {
        ULL tmp = cost[i][k] + cost[k+1][j] + m[i].first*m[k].second*m[j].second;
        if (tmp < best_cost) {
          best_cost = tmp;
          best_cut = k;
        }
      }
      cost[i][j] = best_cost;
      cut[i][j] = best_cut;
    }
  }
  cout << rec(0, n - 1) << endl;
}

using namespace std;
int main() {
  int round = 1;
  while (1) {
    int N;
    cin >> N;
    if (N == 0) break;
    cout << "Case " << round++ << ": ";
    
    vector<pair<int, int>> m;
    for (int i = 0; i < N; ++i) {
      int R, C;
      cin >> R >> C;
      m.push_back(make_pair(R, C));
    }
    solve(m);
  }
}
