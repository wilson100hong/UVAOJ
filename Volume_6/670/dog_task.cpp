#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
using namespace std;

// 2016/10/13
// STAR: *
// SKILL: bipartie match
// TRAP:

struct Point {
  int x;
  int y;
};

string sp(const Point& p) {
  return to_string(p.x) + " " + to_string(p.y); 
}

double dist(const Point& p1, const Point& p2) {
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  double d2 = static_cast<double>(dx*dx + dy*dy);
  return sqrt(d2);
}

bool dfs(const vector<vector<int>>& left,
    vector<bool>& vr, int u,
    vector<int>& ml, vector<int>& mr) {
  for (int v : left[u]) {
    if (!vr[v]) {
      vr[v] = true;
      if (mr[v] == -1 || dfs(left, vr, mr[v], ml, mr)) {
        mr[v] = u;
        ml[u] = v;
        return true;
      } 
    }
  }
  return false;
}

vector<int> bimatch(const vector<vector<int>>& left, int m) {
  int n = left.size();
  vector<int> ml(n, -1);
  vector<int> mr(m, -1);
  // 1. greedy match
  for (int i=0;i<n;++i) {
    for (int j : left[i]) {
      if (mr[j] == -1) {
        ml[i] = j;
        mr[j] = i;
        break;
      }
    }
  }
  // 2. alternating path
  for (int i=0;i<n;++i) {
    if (ml[i] == -1) {
      vector<bool> vr(m, false);  // right visit
      dfs(left, vr, i, ml, mr);
    }
  }
  return ml;
}

void solve(const vector<Point>& checkpoints, const vector<Point>& landmarks) {
  // 1. build bipartie graph
  int n = checkpoints.size(), m = landmarks.size();
  vector<vector<int>> left(n-1, vector<int>());  // human path
  for (int i=0;i<n-1;++i) {
    const Point& p1 = checkpoints[i];
    const Point& p2 = checkpoints[i+1];
    double d = dist(p1, p2);
    for (int j=0;j<m;++j) {
      const Point& p3 = landmarks[j];
      double d2 = dist(p1, p3) + dist(p2, p3);
      if (d2 <= 2*d) {
        left[i].push_back(j);
      }
    }
  }

  // 2. bipartie match
  vector<int> matched = bimatch(left, m);
  int played = 0;
  for (int m : matched) {
    if (m != -1) {
      played++;
    }
  }
  cout << n + played << endl;

  // 3. print output
  cout << sp(checkpoints[0]);
  for (int i=1;i<n;++i) {
    if (matched[i-1] != -1) {
      cout << " " << sp(landmarks[matched[i-1]]);
    }
    cout << " " << sp(checkpoints[i]);
  }
  cout << endl;
}

int main() {
  int L, N, M, x, y;
  cin >> L;
  bool first = true;
  while (L--) {
    cin >> N >> M;
    vector<Point> checkpoints;
    while (N--) {
      cin >> x >> y;
      checkpoints.push_back({x, y});
    }
    vector<Point> landmarks;
    while (M--) {
      cin >> x >> y;
      landmarks.push_back({x, y});
    }

    if (!first) cout << endl;
    first = false;
    solve(checkpoints, landmarks);
  }
}
