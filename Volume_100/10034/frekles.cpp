#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <limits>
using namespace std;

constexpr double kInf = numeric_limits<double>::max() / 4.0;

struct Point {
  double x;
  double y;
};

double dist(const Point& p1, const Point&p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

typedef pair<double, int> DI;

double solve(vector<Point>& points) {
  // TODO
  // 1. build graph
  int N = points.size();
  vector<vector<double>> graph(N, vector<double>(N, kInf));
  for (int i=0;i<N;++i) {
    graph[i][i] = 0;
    for (int j=i+1;j<N;++j) {
      graph[i][j] = graph[j][i] = dist(points[i], points[j]);
    }
  }
  // 2. MST
  set<DI> pq;
  set<int> inserted;
  vector<double> cost(N, kInf);

  pq.insert({0.0, 0});
  double total = 0.0;
  while (!pq.empty()) {
    auto iter = pq.begin();
    double c = iter->first;
    int u = iter->second;
    pq.erase(iter);

    inserted.insert(u);
    //cost[u] = c;
    total += c;
    for (int v=0;v<N;++v) {
      if (v == u || inserted.count(v)) continue;
      double e = graph[u][v];
      if (e < cost[v]) {
        if (cost[v] != kInf) {
          pq.erase({cost[v], v});
        }
        cost[v] = e;
        pq.insert({e, v});
      }
    }
  }
  return total;
}

int main() {
  string line;
  getline(cin, line);
  int T = atoi(line.c_str());
  bool first = true;
  while (T--) {
    getline(cin, line);
    getline(cin, line);
    int N = atoi(line.c_str());
    vector<Point> points;
    for (int n=0;n<N;++n) {
      getline(cin, line);
      stringstream ss(line);
      double x, y;
      ss >> x >> y;
      points.push_back({x, y});
    }
    if (!first) cout << endl;
    first = false;
    cout << fixed << setprecision(2) << solve(points) << endl;
  }
}
