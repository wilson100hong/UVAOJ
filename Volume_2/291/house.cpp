#include <iostream>
#include <iomanip>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> graph = {
  {1, 2, 4},
  {0, 2, 4},
  {0, 1, 3, 4},
  {2, 4},
  {0, 1, 2, 3}
};

set<pair<int,int>> visited;

void print(vector<int>& path) {
  for (int node : path) 
    cout << node + 1;
  cout << endl;
}

void dfs(vector<int>& path, int node) {
  path.push_back(node);
  
  if (path.size() == 9) {
    print(path);
    path.pop_back();
    return;
  }

  for (int next : graph[node]) {
    if (visited.count(make_pair(node, next)) == 0 &&
        visited.count(make_pair(next, node)) == 0) {
      // edge not visited
      visited.insert(make_pair(node, next));

      dfs(path, next);

      visited.erase(make_pair(node, next));
    }
  }
  path.pop_back();
}

int main() {
  vector<int> path = {};
  dfs(path, 0);
}
