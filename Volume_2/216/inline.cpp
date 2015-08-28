// If you saw PE, then check trailing space, tab, .. etc.
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;

#define MAX_N 8
#define MAX_ST 1 << MAX_N
#define INF std::numeric_limits<double>::max()
double dp[MAX_ST][MAX_N];
int to[MAX_ST][MAX_N];

double min(double a, double b) {
  return a < b ? a : b;
}

void clear() {
  for (int st = 0; st < MAX_ST; ++st) {
    for (int n = 0; n < MAX_N; ++n) {
      dp[st][n] = -1;
      to[st][n] = -1;
    }
  }
}

double dist(const pair<int, int>& p1, const pair<int, int>& p2) {
  double dx = p1.first - p2.first;
  double dy = p1.second - p2.second;
  return 16.0 + sqrt(dx*dx + dy*dy);
}

double rec(const vector<pair<int, int>>& pts, int st, int u) {
  if (dp[st][u] >= 0.f)  {
    return dp[st][u];
  }

  double cost = INF;
  for (int v = 0; v < pts.size(); ++v) {
    if (v != u && !(st & (1 << v))) {
      double tmp = dist(pts[u], pts[v]) + rec(pts, st | (1 << v), v);
      if (tmp < cost) {
        cost = tmp;
        to[st][u] = v;
      }
    }
  }
  dp[st][u] = cost;
  return cost;
}

void solve(const vector<pair<int, int>>& pts) {
  clear();
  int n = pts.size();
  int final_st =  (1 << n) - 1;  // where all points visited
  for (int i = 0; i < n; ++i) {
    dp[final_st][i] = 0.f;
  }

  double cost = INF;
  int start = -1;
  for (int i = 0; i < n; ++i) {
    int st = 1 << i;
    double tmp = rec(pts, st, i);
    if (tmp < cost) {
      cost = tmp;
      start = i;
    }
  }
  int st = 1 << start;

  while (1) {
    if (to[st][start] == -1) break;
    const pair<int, int>& u = pts[start];
    const pair<int, int>& v = pts[to[st][start]];
    cout << "Cable requirement to connect (" << u.first << "," << u.second << ") to ("
                                             << v.first << "," << v.second << ") is " 
                                             << fixed << setprecision(2) << dist(u, v) << " feet." << endl;
    start = to[st][start];
    st |= (1 << start);
  }
  cout << "Number of feet of cable required is " << fixed << setprecision(2) << cost << "." << endl;
}

int main() {
  int round = 1;
  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;
    vector<pair<int, int>> pts;
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      pts.push_back(make_pair(x, y));
    }
    cout << "**********************************************************" << endl;
    cout << "Network #" << round++ << endl;
    solve(pts);
  }
}
