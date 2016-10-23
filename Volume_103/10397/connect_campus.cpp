#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

// 2016/10/23
// STAR: *
// SKILL: kruskal, disjoint set
// TRAP: 1) priority queue from large value to small value!
//       2) ngroups only decrease when join happen!

int get_group(int u, vector<int>& group) {
  if (group[u] != u) {
    group[u] = get_group(group[u], group);
  }
  return group[u];
}

void union_group(int u, int v, vector<int>& group) {
  int gu = get_group(u, group), gv = get_group(v, group);
  if (gu != gv) {
    group[gu] = gv;
  }
}

struct Building {
  int x;
  int y;
};

double dist(const Building& b1, const Building& b2) {
  long long dx = b1.x - b2.x;
  long long dy = b1.y - b2.y;
  return sqrt(static_cast<double>(dx*dx + dy*dy));
}

struct Cable {
  double len;
  int u;
  int v;
  // need to be friend.. it is not member function!
  friend bool operator >(const Cable& lhs, const Cable& rhs) {
    return lhs.len > rhs.len;
  }
};

int main() {
  int N, M;
  while (cin >> N) {
    vector<Building> buildings;
    vector<int> group;
    for (int i=0;i<N;++i) {
      Building b;
      cin >> b.x >> b.y;
      buildings.push_back(b);
      group.push_back(group.size());
    }

    cin >> M;

    // union join
    int ngroups = N;
    while (M--) {
      int u, v;
      cin >> u >> v;
      u--; v--;  // 0-based
      if (get_group(u, group) != get_group(v, group)) {
        union_group(u, v, group);
        ngroups--;
      }
    }
    
    // put all edges in priority queue
    priority_queue<Cable, vector<Cable>, greater<Cable>> pq;
    for (int u=0;u<N;++u) {
      for (int v=u+1;v<N;++v) {
        if (get_group(u, group) != get_group(v, group)) {
          double len = dist(buildings[u], buildings[v]);
          pq.push({len, u, v});
        }
      }
    }
    double cost = 0.0;
    // do Kruskal
    while (ngroups > 1 && !pq.empty()) {
      Cable cable = pq.top();
      pq.pop();
      int u = cable.u, v = cable.v;
      if (get_group(u, group) != get_group(v, group)) {
        union_group(u, v, group);
        ngroups--;
        cost += cable.len;
      }
    }
    cout << fixed;
    cout << setprecision(2) << cost << endl;
  }
}
