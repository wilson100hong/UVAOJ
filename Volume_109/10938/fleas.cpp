#include <algorithm> 
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
struct Node {
  int parent;  // set in Tarjan (DFS)
  int group;
  bool visit;
  vector<int> neighbors;
};

vector<Node> tree;
vector<vector<int>> LCA;

int find(int u) {
  if (tree[u].group != u) {
    tree[u].group = find(tree[u].group);
  }
  return tree[u].group;
}

void tarjan(int u) {
  if (tree[u].visit) return;
  tree[u].visit = true;

  LCA[u][u] = u;
  for (int v = 0; v < tree.size(); ++v) {
    if (v != u && tree[v].visit) {
      LCA[u][v] = LCA[v][u] = find(v);
    }
  }

  for (int v : tree[u].neighbors) {
    if (!tree[v].visit) {
      tarjan(v);
      tree[v].group = u;
      tree[v].parent = u;
    }
  }
}

void build(int root) {
  LCA.clear();
  LCA.assign(tree.size(), vector<int>(tree.size(), -1));

  tarjan(root);
}

vector<int> path_up(int node, int ancestor) {
  vector<int> path;
  while (node != ancestor) {
    path.push_back(node);
    node = tree[node].parent;
  }
  return path;
}

void solve(const vector<int>& path) {
  int i = 0, j = path.size() - 1;
  while (i < j) {
    ++i;
    --j;
  }
  int pi = path[i];
  int pj = path[j];
  if (pi == pj) {
    cout << "The fleas meet at " << pi << "." << endl;
  } else {
    if (pi > pj)  swap(pi, pj);
    // i always < j
    cout << "The fleas jump forever between " << pi << " and " << pj << "." << endl;
  }
}

int main() {
  int n, l, a, b;
  int round = 0;
  while (1) {
    cin >> n;
    if (n == 0) break;

    // reset tree
    tree.clear();
    for (int i = 0; i < n + 1; ++i) {
      tree.push_back({i, i, false, {}});
    }
    for (int i = 0; i < n - 1; ++i) {
      cin >> a >> b;
      tree[a].neighbors.push_back(b);
      tree[b].neighbors.push_back(a);
    }

    build(1);  // anyone can be root
    cin >> l;
    for (int i = 0; i < l; ++i) {
      cin >> a >> b;
      int lca = LCA[a][b];

      vector<int> path = path_up(a, lca);
      path.push_back(lca);
      vector<int> path_from_b = path_up(b, lca);
      path.insert(path.end(), path_from_b.rbegin(), path_from_b.rend());
      solve(path);
    }
  }
}
