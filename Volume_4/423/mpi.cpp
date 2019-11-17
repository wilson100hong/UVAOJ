#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <tuple>
#include <cstdlib>
#include <sstream>
using namespace std;

constexpr int kInf = std::numeric_limits<int>::max() / 4;
typedef pair<int, int> II;  // Distance, node

int solve(vector<vector<int>>& graph) {
  int N = graph.size();
  vector<int> distances(N, kInf);
  set<II> pq;  // Priority queue.
  pq.insert({0, 0});
  distances[0] = 0;

  while (!pq.empty()) {
    auto iter = pq.begin();
    int dist, u;
    tie(dist, u) = *iter;
    pq.erase(iter);
    for (int v=0;v<N;++v) {
      if (graph[u][v] == kInf) continue;  // Noe edge
      int new_dist = dist + graph[u][v];
      if (new_dist < distances[v]) {
        if (distances[v] != kInf) {
          pq.erase({distances[v], v});
        }
        distances[v] = new_dist;
        pq.insert({new_dist, v});
      }
    }
  }

  int time = 0;
  for (int i=0;i<N;++i) {
    time = max(time, distances[i]);
  }

  return time;
}

int main() {
  string line;
  while (getline(cin, line)) {
    int N = atoi(line.c_str());
    vector<vector<int>> graph(N, vector<int>(N, kInf));
    for (int i=0;i<N;++i) {
      graph[i][i] = 0;
    }
    string temp;
    for (int i=1;i<N;++i) {
      getline(cin, line);
      stringstream ss(line);

      for (int j=0;j<i;++j) {
        ss >> temp;
        if (temp != "x") {
          int cost = atoi(temp.c_str());
          graph[i][j] = graph[j][i] = cost;
        }
      }
    }
    cout << solve(graph) << endl;
  }
}
