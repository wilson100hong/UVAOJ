#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <limits>

using namespace std;

constexpr int kMin = numeric_limits<int>::min();

constexpr int kTypeSize = 3;
// 0: all ways
// 1: down, left
// 2: down, right

struct Node {
  int row;
  int col;
  int val;
  int type;
  //set<int> prev;
  set<int> next;
};

void DFS(const vector<Node>& nodes, int u, vector<bool>& visit, vector<int>& order) {
  visit[u] = true;
  for (int v : nodes[u].next) {
    if (!visit[v]) {
      DFS(nodes, v, visit, order);
    }
  }
  order.push_back(u);
}

int ToIndex(int N, int i, int j, int type) {
  int offset = (i * N + j) * kTypeSize;
  return offset + type;
}

int Solve(const vector<Node>& nodes, int N, int K) {
  // Sort by topological order
  vector<bool> visit(nodes.size(), false);
  vector<int> order;
  DFS(nodes, 0, visit, order);

  vector<map<int, int>> dp(nodes.size(), map<int, int>());
  // dp initialization for first row.
  for (int u=0;u < kTypeSize;++u) {
    int num_neg = nodes[u].val < 0 ? 1 : 0;
    dp[u][num_neg] = nodes[u].val;
  }

  for (int i=order.size()-1;i>=0;i--) {
    int u = order[i];
    const auto& node = nodes[u];

    for (const auto& kv : dp[u]) {
      if (kv.second == kMin) continue;  // Not reachable
      for (int v : node.next) {
        int num_neg = nodes[v].val < 0 ? kv.first + 1 : kv.first;
        if (num_neg > K) continue;
        if (dp[v].count(num_neg) == 0) dp[v][num_neg] = kMin;
        dp[v][num_neg] = max(dp[v][num_neg], kv.second + nodes[v].val);
      }
    }
  }

  int ans = kMin;
  for (int u=ToIndex(N, N-1, N-1, 0); u<nodes.size(); ++u) {
    for (const auto& kv : dp[u]) {
      ans = max(ans, kv.second);
    }
  }
  return ans;
}


int main() {
  int N, K;
  int case_num = 1;
  int val;
  while (cin >> N >> K) {
    if (N == 0 && K == 0) break;
    vector<Node> nodes(N*N*kTypeSize, Node());  // Create 3 * N^2 nodes
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        cin >> val;
        for (int t=0;t<kTypeSize;++t) {
          auto& node = nodes[ToIndex(N, i, j, t)];
          node.row = i;
          node.col = j;
          node.val = val;
          node.type = t;
        }
        // Connect edges
        if (i < N-1) { // has down
          nodes[ToIndex(N, i, j, 0)].next.insert(ToIndex(N, i+1, j, 0));
          nodes[ToIndex(N, i, j, 1)].next.insert(ToIndex(N, i+1, j, 0));
          nodes[ToIndex(N, i, j, 2)].next.insert(ToIndex(N, i+1, j, 0));
        }
        if (j > 0) {  // has left
          nodes[ToIndex(N, i, j, 0)].next.insert(ToIndex(N, i, j-1, 1));
          nodes[ToIndex(N, i, j, 1)].next.insert(ToIndex(N, i, j-1, 1));
        }
        if (j < N - 1) {  // has right
          nodes[ToIndex(N, i, j, 0)].next.insert(ToIndex(N, i, j+1, 2));
          nodes[ToIndex(N, i, j, 2)].next.insert(ToIndex(N, i, j+1, 2));
        }
      }
    }

    int ans = Solve(nodes, N, K);

    cout << "Case " << case_num++ << ": ";
    if (ans == kMin) cout << "impossible";
    else cout << ans;
    cout << endl;
  }
}
