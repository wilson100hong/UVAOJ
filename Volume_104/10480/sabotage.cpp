#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

// 2016/10/25
// STAR: 
// SKILL: min cut, edmond-karp
// TRAP: 1) list min cuts after finding max flow

#define START 1
#define END 2

typedef long long ll;
ll INF = 1e8;

ll min(ll a, ll b) {
  return a < b ? a : b;
}

ll find_path(
    vector<unordered_map<int, ll>>& capacity, 
    vector<unordered_map<int, ll>>& flow,
    vector<int>& path) {
  int n = capacity.size();
  queue<int> que;
  que.push(START);

  vector<bool> visit(n, false);
  visit[START] = true;
  vector<int> prev(n, -1);

  bool found = false;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (u == END) {
      found = true;
      break;
    }
    for (auto& v_f : flow[u]) {
      int v = v_f.first;
      if (!visit[v]) {
        if (capacity[u][v] > flow[u][v]) {
          // has residual 
          visit[v] = true;
          prev[v] = u;
          que.push(v);
        }
      }
    }
  }
  
  if (found) {
    int v = END;
    ll max_flow = INF;
    while (1) {
      path.push_back(v);
      int u = prev[v];
      if (u == -1) break;
      max_flow = min(max_flow, capacity[u][v] - flow[u][v]);
      v = u;
    }
    reverse(path.begin(), path.end());
    return  max_flow;
  }
  return 0;
}

void update_flow(
    const vector<int>& path,
    vector<unordered_map<int, ll>>& flow, ll f) {
  for (int i=0;i<path.size()-1;++i) {
    int u = path[i], v = path[i+1];
    flow[u][v] += f;
    flow[v][u] = -1*flow[u][v];
  }
}

void solve(
    vector<unordered_map<int, ll>>& capacity, 
    vector<unordered_map<int, ll>>& flow) {
  int n = capacity.size();
  // doing edmond karp
  while (1) {
    vector<int> path;
    ll f = find_path(capacity, flow, path);
    if (f==0) break;
    update_flow(path, flow, f);
  }

  // BFS find bottlenecks
  queue<int> que;
  que.push(START);
  vector<bool> visit(n, false);
  visit[START] = true;

  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (auto& v_f : flow[u]) {
      int v = v_f.first;
      if (flow[u][v] < capacity[u][v]) {
        if (!visit[v]) {
          visit[v] = true;
          que.push(v);
        }
      }
      // else, ignore the edge
    }
  }

  set<pair<int, int>> bottlenecks;
  for (int u=0;u<n;++u) {
    for (auto& v_f : flow[u]) {
      int v = v_f.first;
      if (visit[u] && !visit[v]) {
        bottlenecks.insert({u, v});
      }
    }
  }
  for (auto& u_v : bottlenecks) {
    cout << u_v.first << " " << u_v.second << endl;
  }
  cout << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    if (n==0 && m==0) break;
    vector<unordered_map<int, ll>> capacity(n+1, unordered_map<int,ll>());  // 1-based
    vector<unordered_map<int, ll>> flow(n+1, unordered_map<int,ll>());  // 1-based

    for (int i=0;i<m;++i) {
      int u, v;
      ll cap;
      cin >> u >> v >> cap;
      capacity[u][v] = cap;
      capacity[v][u] = cap;
      flow[u][v] = 0;
      flow[v][u] = 0;
    }
    solve(capacity, flow);
  }
}

