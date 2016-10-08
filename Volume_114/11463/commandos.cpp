#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

// 2016/10/08
// SKILL: floyd warsahll
// STAR: **
// TRAP: 1) make sure you understand this problem. It is asking the maximum length
//          of shortest path passing node

int MAX = numeric_limits<int>::max() / 8;

int solve(vector<vector<int>>& graph, int s, int d) {
  int n = graph.size();
  // floyd warshall
  for (int k=0;k<n;++k) {
    for (int i=0;i<n;++i) {
      for (int j=0;j<n;++j) {
        if (graph[i][k] + graph[k][j] < graph[i][j]) {
          graph[i][j] = graph[i][k] + graph[k][j];
        }
      }
    }
  }

  int maximum = 0;
  for (int k=0;k<n;++k) {
    int dist = graph[s][k] + graph[k][d];
    if (dist > maximum) {
      maximum = dist;
    }
  }
  return maximum;
}

int main() {
  int T;
  cin >> T;
  for (int t=1;t<=T;++t) {
    int N, R;
    cin >> N >> R;
    vector<vector<int>> graph(N, vector<int>(N, MAX));
    for (int i=0;i<N;++i) {
      graph[i][i] = 0;
    }
    for (int r=0;r<R;++r) {
      int from, to;
      cin >> from >> to;
      graph[from][to] = graph[to][from] = 1;
    }
    int s, d;
    cin >> s >> d;
    cout << "Case " << t << ": " << solve(graph, s, d) << endl;
  }
}
