// TODO: totally wrong
// 2016/09/30
// SKILLS: dp, dp in tree, weird math
// STARS: *****
// trap: 1) max number of colors you need is 15... magic!
//       2) find tree root
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <cstring>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

#define MAX_N 10010
#define MAX_COLOR 15
int DP[MAX_N][MAX_COLOR];

int min(int a, int b) {
  return a < b ? a : b;
}

/*
string dump(const State& state) {
  return "(" + to_string(state.one) + ", " + to_string(state.two) + ")";
}
*/

int optimal_subtree(const vector<vector<int>>& tree, int node, int parent_color) {
  int ans = numeric_limits<int>::max();
  for (int color=1;color<=MAX_COLOR;++color) {
    if (color == parent_color) continue;
    int sum;
    if (DP[node][color] != 0) {
      sum = DP[node][color];
    } else {
      sum = color;
      for (int child : tree[node]) {
        sum += optimal_subtree(tree, child, color);
      }
      DP[node][color] = sum;
    }
    ans = min(ans, sum);
  }
  return ans;
}

void dfs(
    const vector<vector<int>>& tree,
    int node,
    vector<int>& ordering,
    vector<bool>& visit) {
  visit[node] = true;
  for (int child : tree[node]) {
    if (!visit[child]) {
      dfs(tree, child, ordering, visit);
    }
  }
  ordering.push_back(node);
}

int find_root(const vector<vector<int>>& tree) {
  int n = tree.size();
  vector<int> ordering;
  vector<bool> visit(n, false);
  for (int i=n-1;i>=0;--i) {
  //for (int i=0;i<n;++i) {
    if (!visit[i]) {
      dfs(tree, i, ordering, visit);
    }
  }
  return ordering.back();
}

int solve(const vector<vector<int>>& tree) {
  int n = tree.size();
  int root = find_root(tree);
  //cout << "root: " << root << endl;
  memset(DP, 0, sizeof(DP[0][0])*MAX_N*MAX_COLOR);
  return optimal_subtree(tree, root, -1);
}

int main() {
  int N;
  char colon;
  while (1) {
    eatline() >> N;
    if (N == 0) break;
    vector<vector<int>> tree(N, vector<int>());
    for (int i=0;i<N;++i) {
      stringstream& ss = eatline();
      int u;
      ss >> u; 
      vector<int>& vertex = tree[u];
      ss >> colon;
      while (ss >> u) {
        vertex.push_back(u);
      }
      // parse line to tree
    }

    /*
    for (int i=0;i<N;++i) {
      cout << "[" << i << "]: ";
      for (int c : tree[i]) {
        cout << c << " ";
      }
      cout << endl;
    }
    */

    cout << solve(tree) << endl;
    eatline();
  }
}
