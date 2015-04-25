// I use Krusal's in this problem since we need to union edges by the ordering of its weight. 
// Prim probably does not works because it consider the "distance between nodes" instead of "weight of edge".
// Eg.
//
// a -- b -- c -- d
// |______________|
//
// (a, b) = 20
// (b, c) = 30
// (c, d) = 20
// (a, d) = 10000
// 
// The answer is D = 20, with satelite between (b, c)
// If we use Prim from a, it will consider a->b->c->d in order, thus not knowing where is the
// best place to use satelite.
#include <algorithm> 
#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <vector>
#include <math.h> 

using namespace std;

struct Edge {
  int u;
  int v;
  int cost;
};

bool operator<(const Edge& e1, const Edge& e2) {
  return e1.cost < e2.cost;
}

// disjoint set
int find(vector<int>& parents , int u) {
  if (parents[u] != u) {
    parents[u] = find(parents, parents[u]);
  }
  return parents[u];
}

void merge(vector<int>& parents, int u, int v) {
  parents[find(parents, v)] = find(parents, u);
}

int main() {
  // Read input
  int T, S, P, X, Y;
  cin >> T;
  vector<pair<int, int>> outposts;
  vector<Edge> edges;
  vector<int> parents;
  while (T-- > 0) {
    cin >> S >> P;
    outposts.clear();
    parents.clear();
    for (int p = 0; p < P; ++p) {
      cin >> X >> Y;
      outposts.push_back(make_pair(X, Y));
      parents.push_back(p);  // disjoint set default parents
    }

    edges.clear();
    for (int i = 0; i < outposts.size(); ++i) {
      for (int j = i + 1; j < outposts.size(); ++j) {
        int dx = outposts[j].first - outposts[i].first;
        int dy = outposts[j].second - outposts[i].second;
        int cost = dx * dx + dy * dy;
        edges.push_back({i, j, cost});
        edges.push_back({j, i, cost});
      }
    }
    sort(edges.begin(), edges.end());

    int max = 0;
    // Kruskal
    auto iter = edges.begin();
    for (int i = 0; i < P - S  && iter != edges.end(); ++i) {
      // if forms cycle (same set)
      while (find(parents, iter->u) == find(parents, iter->v)) {
        ++iter;
      }

      max = iter->cost;
      merge(parents, iter->u, iter->v);
      ++iter;
    }
    double ans = sqrt(max);
    cout << fixed << setprecision(2) << ans << endl;
  }
}
