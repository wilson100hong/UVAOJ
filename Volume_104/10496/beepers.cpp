#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits>

using namespace std;

struct Point {
  int x;
  int y;
};

constexpr int MAX = std::numeric_limits<int>::max() / 4;  // Avoid overflow
constexpr int UNDEF = MAX;

int abs(int x) {
  return x > 0 ? x : -x;
}

int dist(const Point& p1, const Point& p2) {
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return abs(dx) + abs(dy);
}

int rec(const vector<Point>& points, int i, int state, vector<vector<int>>& dp) {
  if (dp[i][state] != UNDEF) return dp[i][state];

  int n = points.size();

  int best = MAX;
  for (int j=0;j<n;++j) {
    if (state & (1 << j)) continue;
    int next_state = state | (1 << j);

    int moves = dist(points[i], points[j]) + rec(points, j, next_state, dp);
    if (moves < best) {
      best = moves;
    }
  }

  dp[i][state] = best;
  return best;
}

int solve(const vector<Point>& points, const Point& karel) {
  int n = points.size();

  int state = 0;  // no beerps picked

  // dp[i][state] means additional movement needs when kerel is at i, with state
  vector<vector<int>> dp(n, vector<int>(1<<n, UNDEF));

  // initialize
  for (int i=0;i<n;++i) {
    int state = (1 << n) - 1;
    dp[i][state] = dist(points[i], karel);
  }

  int best = MAX;
  for (int i=0;i<n;++i) {
    int state = 1 << i;
    int move = dist(karel, points[i]) + rec(points, i, state, dp);
    if (move < best) {
      best = move;
    }
  }
  return best;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    // seems w and h is not used?
    int w, h;  // w -> x, h -> y
    cin >> w >> h;
    Point karel;
    cin >> karel.x >> karel.y;
    int N;
    cin >> N;
    vector<Point> beepers;
    while (N--) {
      Point p;
      cin >> p.x >> p.y;
      beepers.push_back(p);
    }
    cout << "The shortest path has length " << solve(beepers, karel) << endl;
  }
}

