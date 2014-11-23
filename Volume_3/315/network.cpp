#include <iostream>
#include <sstream>
#include <vector>

#define NOT_VISIT -1
using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

void dfs(const vector<vector<int> >& edges,
         vector<int>& visit,
         vector<int>& low,
         vector<int>& parent,
         int node,
         int& order) {
  visit[node] = low[node] = order++;
  for (int i = 0; i < edges[node].size(); ++i) {
    int to = edges[node][i];
    if (visit[to] == NOT_VISIT) {
      parent[to] = node;
      dfs(edges, visit, low, parent, to, order);
      low[node] = min(low[node], low[to]);
    } else if (to != parent[node]) {
      // skip 'to' when to is node's parent
      low[node] = min(low[node], visit[to]);
    }
  }
}

void solve(const vector<vector<int> >& edges) {
  int n = edges.size();
  vector<int> visit(n, NOT_VISIT);
  vector<int> low;
  vector<int> parent;
  for (int i = 0; i < n; ++i) {
    low.push_back(i);
    parent.push_back(i);
  }

  // 1. DFS
  int order = 0;
  for (int i = 0; i < n; ++i) {
    if (visit[i] == NOT_VISIT) { 
      parent[i] = i;
      dfs(edges, visit, low, parent, i, order);
    }
  }

  // 2. judge articulation point
  vector<int> articulation_pts;
  for (int i = 0; i < n; ++i) {
    if (parent[i] == i) {  // i is root
      int child = 0;
      for (int j = 0; j < n; ++j) {
        if (j != i && parent[j] == i)
          child++;
      }
      if (child > 1) {
        articulation_pts.push_back(i);
      }
    } else {
      bool is_articulation = false;
      for (int j = 0; j < n; ++j) {
        if (j != i && parent[j] == i && low[j] >= visit[i]) {
          is_articulation = true;
          break;
        }
      }
      if (is_articulation) 
        articulation_pts.push_back(i);
    }
  }
  cout << articulation_pts.size() << endl;
}

int main () {
  int n;
  while (1) {
    cin >> n;
    if (n == 0)  break;
    string line;
    vector<vector<int> > edges;
    for (int i = 0; i < n; ++i) 
      edges.push_back(vector<int>());

    while (getline(cin, line)) {
      if (line == "0") break;
      stringstream ss(line);
      int u, v;
      ss >> u;
      while (ss >> v) {
        // convert node to 0-indexed for easier processing.
        edges[u - 1].push_back(v - 1);
        edges[v - 1].push_back(u - 1);
      }
    }
   solve(edges);
  }
}
