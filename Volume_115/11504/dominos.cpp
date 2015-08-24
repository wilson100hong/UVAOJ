#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(const vector<vector<int> >& graph,
    vector<bool>& visited,
    stack<int>& order,
    int node) {
  visited[node] = true;
  for (int i = 0; i < graph[node].size(); ++i) {
    int neighbor = graph[node][i];
    if (!visited[neighbor]) {
      dfs(graph, visited, order, neighbor);
    }
  }
  order.push(node);
}

void solve(const vector<vector<int> >& graph) { stack<int> order;
  vector<bool> visited(graph.size(), false);
  // node starting from 1
  for (int node = 1; node < graph.size(); ++node) {
    if (!visited[node]) {
      dfs(graph, visited, order, node);
    }
  }

  stack<int> dummy;
  visited.assign(graph.size(), false);
  int cnt = 0;
  while (!order.empty()) {
    int node = order.top();
    order.pop();
    if (!visited[node]) {
      dfs(graph, visited, dummy, node);
      cnt++;
    }
  }
  cout << cnt << endl;
} 

int main() {
  int rounds;
  cin >> rounds;
  while (rounds-- > 0) {
    int num_nodes, num_lines;
    cin >> num_nodes >> num_lines;
    vector<vector<int> > graph(num_nodes + 1, vector<int>());
    while (num_lines-- > 0) {
      int from, to;
      cin >> from >> to;
      graph[from].push_back(to);
    }
    solve(graph);
  }
}
