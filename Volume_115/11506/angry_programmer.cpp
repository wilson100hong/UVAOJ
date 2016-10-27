#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <algorithm>
using namespace std;

// 2016/10/26
// STAR: **
// SKILL: min-cut, edmond-karp
// TRAP: 1) when iterate in BFS, you need to iterate flow[] because 
//          residuals are only in flow[]! (not in cap!)
//          I am just too lucky not meet this bug before!

#define START 0
#define END 1

tuple<int, int> break_node(int u, int M) {
  if (u==1) return make_tuple(START, START);
  if (u==M) return make_tuple(END, END);
  return make_tuple((u-1)*2, (u-1)*2+1);
}

typedef long long int ll;
ll INF = 1e8;

ll min(ll a, ll b) {
  return a < b ? a : b;
}

ll find_path(
    vector<unordered_map<int, ll>>& cap,
    vector<unordered_map<int, ll>>& flow,
    vector<int>& path) {
  int n = cap.size();
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
    // !!! iterate on flow[] to includes residual!
    for (auto& v_c : flow[u]) {
      int v = v_c.first;
      if (!visit[v]) {
        // cout << "u: " << u << "  v: "<< v << " cap: " << cap[u][v] << "  flow: " << flow[u][v] << endl;
        if (cap[u][v] > flow[u][v]) {
          visit[v] = true;
          prev[v] = u;
          que.push(v);
        }
      }
    }
  }

  if (!found) return 0;

  int v = END;
  path.push_back(v);
  ll res = INF;
  while(1) {
    int u = prev[v]; 
    if (u == -1) break;
    res = min(res, cap[u][v] - flow[u][v]);
    v = u;
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return res;
}

void update_flow(
    const vector<int>& path,
    vector<unordered_map<int, ll>>& cap,
    vector<unordered_map<int, ll>>& flow, ll f) {
  for (int i=0;i<path.size()-1;++i) {
    int u = path[i], v = path[i+1];
    flow[u][v] += f;
    flow[v][u] = -1*flow[u][v];
  }
}

ll edmond_karp(
    vector<unordered_map<int, ll>>& cap,
    vector<unordered_map<int, ll>>& flow) {
  ll sum = 0;
  while (1) {
    vector<int> path;
    ll f = find_path(cap, flow, path);
    if (f==0) break;
    sum += f;

    update_flow(path, cap, flow, f);
  }
  return sum;
}

int main() {
  int M, W;
  int idx = 1;
  while (cin >> M >> W) {
    if (M==0 && W==0) break;
    int n = 2*(M-1); 
    vector<unordered_map<int, ll>> cap(n, unordered_map<int, ll>());
    vector<unordered_map<int, ll>> flow(n, unordered_map<int, ll>());

    // we map 1 -> 0, M -> 1
    // for other machine i, create nodes 2*(i-1) and 2*(i-1)+1
    // where 2*(i-1) is input, 2*(i-1)+1 is output
    for (int i=0;i<M-2;++i) {
      int u;
      ll cost;
      cin >> u >> cost;
      int u1, u2;
      tie(u1, u2) = break_node(u, M);
      cap[u1][u2] = cap[u2][u1] = cost;
      flow[u1][u2] = flow[u2][u1] = 0;
    }
    for (int i=0;i<W;++i) {
      int j, k;
      ll cost;
      cin >> j >> k >> cost;
      // handle 1 and M
      int j1, j2, k1, k2;
      tie(j1, j2) = break_node(j, M);
      tie(k1, k2) = break_node(k, M);
      cap[k2][j1] = cap[j2][k1] = cost;
      flow[k2][j1] = flow[j2][k1] = 0;
    }
    cout << edmond_karp(cap, flow) << endl;
    idx++;
  }
}
