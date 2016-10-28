#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <tuple>
using namespace std;
// 2016/10/27
// STAR: *
// SKILL: max-flow, edmond-karp
// TRAP

int W, H, B;

tuple<int, int> transform(int x, int y) {
  int t = y*W+x;
  return make_tuple(t, t+W*H);
}

tuple<int, int> inv(int index) {
  // return {x, y}
  if (index >= W*H) index -= W*H;
  return make_tuple(index%H, index/H);
}

void dump(const tuple<int, int>& tt) {
  cout << "(" << get<0>(tt) << "," << get<1>(tt) << ")" << endl;
}

bool inbound(int x, int y) {
  return 0<=x && x < W && 0<=y && y < H;
}

int DX[] = {-1, 1, 0, 0};
int DY[] = {0, 0, -1, 1};

int min(int a, int b) {
  return a < b ? a : b;
}

// path from start -> end
int find_path(
    vector<unordered_map<int, int>>& cap,
    vector<unordered_map<int, int>>& flow,
    int start, int end,
    vector<int>& path) {
  int n = cap.size();

  // BFS
  vector<int> prev(n, -1);
  vector<bool> visit(n, false);
  visit[start] = true;
  bool arrive = false;
  queue<int> que;
  que.push(start);

  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (u==end) {
      arrive = true;
      break;
    }
    for (auto& v_f : flow[u]) {
      int v = v_f.first;
      if (!visit[v]) {
        if (cap[u][v] > flow[u][v]) {
          visit[v] = true;
          prev[v] = u;
          que.push(v);
        }
      }
    }
  }

  if (!arrive) {
    return 0;
  }

  // build path
  int f = 1e8;  // any value > 1 is fine
  int v = end;
  while (1) {
    path.push_back(v);
    int u = prev[v];
    if (u == -1) break;
    f = min(f, cap[u][v] - flow[u][v]);
    v = u;
  }
  reverse(path.begin(), path.end());
  return f;
}

void update_flow(
    vector<unordered_map<int, int>>& flow,
    vector<int>& path,
    int f) {
  for (int i=0;i<path.size()-1;++i) {
    int u = path[i], v = path[i+1];
    flow[u][v] += f;
    flow[v][u] = -1 *flow[u][v];
  }
}

int max_flow(
    vector<unordered_map<int, int>>& cap,
    vector<unordered_map<int, int>>& flow,
    int start, int end) {
  int res = 0;
  while (1) {
    vector<int> path;
    int f = find_path(cap, flow, start, end, path);
    if (f == 0) break;
    res += f;
    update_flow(flow, path, f);
  }
  return res;
}

int main() {
  int P;
  cin >> P;
  while (P--) {
    cin >> W >> H >> B;

    // build graphs
    // every point create two nodes
    // (x, y) -> [y*W+x], [y*W+x + W*H]
    // where [y*w+x] for input, [y*W+x + W*H] for output
    vector<unordered_map<int, int>> cap(W*H*2, unordered_map<int, int>());
    vector<unordered_map<int, int>> flow(W*H*2, unordered_map<int, int>());
    for (int x=0;x<W;++x) {
      for (int y=0;y<H;++y) {
        int in, out;
        tie(in, out) = transform(x, y);
        cap[in][out] = cap[out][in] = 1;
        flow[in][out] = flow[out][in] = 0;
        // build edge from node toward neighbors only.
        for (int d=0;d<4;++d) {
          int nx = x+DX[d], ny = y+DY[d];
          if (inbound(nx, ny)) {
            int nin, nout;
            tie(nin, nout) = transform(nx, ny);
            cap[out][nin] = 1;
            cap[nin][out] = 0;  // for backflow
            flow[out][nin] = flow[nin][out] = 0;
          }
        }
        
      }
    }

    // bind banks to start point
    int start = cap.size();
    cap.push_back(unordered_map<int, int>());
    flow.push_back(unordered_map<int, int>());
    for (int i=0;i<B;++i) {
      int x, y;
      cin >> x >> y;
      x--; y--;  // 0-based coordinates
      
      int in, out;
      tie(in, out) = transform(x, y);
      cap[start][in] = 1;
      cap[in][start] = 0;
      flow[start][in] = flow[in][start] = 0;
    }

    // bind exists to end point
    int end = cap.size();
    cap.push_back(unordered_map<int, int>());
    flow.push_back(unordered_map<int, int>());
    for (int y=0;y<H;++y) {
      vector<int> xs = {0, W-1};
      for (int x : xs) {
        int in, out;
        tie(in, out) = transform(x, y);
        cap[out][end] = 1;
        cap[end][out] = 0;
        flow[out][end] = flow[end][out] = 0;
      }
    }
    for (int x=1;x<W-1;++x) {
      vector<int> ys = {0, H-1};
      for (int y : ys) {
        int in, out;
        tie(in, out) = transform(x, y);
        cap[out][end] = 1;
        cap[end][out] = 0;
        flow[out][end] = flow[end][out] = 0;
      }
    }
    int mf = max_flow(cap, flow, start, end); 
    if (mf == B) {
      cout << "possible" << endl;
    } else {
      cout << "not possible" << endl;
    }

  }
}
