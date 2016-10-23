#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

// 2016/10/23
// STAR: *
// SKILL: kruskal
// TRAP: 1) it is possible there is no valid MST when you remove an edge!

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int get_group(int u, vector<int>& groups) {
  if (groups[u] != u) {
    groups[u] = get_group(groups[u], groups);
  }
  return groups[u];
}

void union_group(int u, int v, vector<int>& groups) {
  int gu = get_group(u, groups), gv = get_group(v, groups);
  if (gu != gv) {
    groups[gu] = gv;
  }
}

struct Edge {
  int u;
  int v;
  int w;
  int index;
};

bool compare_edge(const Edge& e1, const Edge& e2) {
  return e1.w < e2.w;
}

// edges must be sorted
// NOTE: it is possible MST cannot be formed!
int kruskal(int n, vector<Edge>& edges, const vector<bool>& must_used,
    int invalid_edge, set<int>& picked) {

  int m = edges.size();
  vector<int> groups(n, 0);
  for (int i=0;i<n;++i) {
    groups[i] = i;
  }
  int ngroups = n;

  int cost = 0;
  for (int i=0;i<m;++i) {
    const Edge& edge = edges[i];
    if (edge.index != invalid_edge &&
        (must_used[edge.index]   // we assume edge must-be-used always join two different sets
         || get_group(edge.u, groups) != get_group(edge.v, groups))) {
      union_group(edge.u, edge.v, groups);
      picked.insert(edge.index);
      cost += edge.w;
      ngroups--;

    }
    if (ngroups == 1) break;
  }
  return ngroups == 1 ? cost : 1e8;
}

int main() {
  int T, N, M, A, B, C;
  cin >> T;
  while (T--) {
    cin >> N >> M;
    vector<Edge> edges;
    for (int i=0;i<M;++i) {
      cin >> A >> B >> C;
      A--; B--;  // 0-based
      edges.push_back({A, B, C, i});
    }
    sort(edges.begin(), edges.end(), compare_edge);

    // doing kruskal for 1st time
    vector<bool> used(M, false);
    set<int> picked;
    int best_mst = kruskal(N, edges, used, -1, picked);

    // update used
    for (int ei : picked) {
      used[ei] = true;
    }
    int second_mst = 1e8;
    // for each picked edge, doing kruskal by invalidating that edge
    for (int ei : picked) {
      used[ei] = false;
      set<int> dummy;
      int mst = kruskal(N, edges, used, ei, dummy);
      if (mst < second_mst) {
        second_mst = mst;
      }
      used[ei] = true;
    }

    cout << best_mst << " " << second_mst << endl;
  }
}
