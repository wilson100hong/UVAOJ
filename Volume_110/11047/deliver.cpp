#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
using namespace std;

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

void Floyd(vector<vector<int>>& graph, vector<vector<int>>& next) {
  int N = graph.size();
  for (int k=0;k<N;++k) {
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        if (graph[i][k] != -1 && graph[k][j] != -1) {
          int d = graph[i][k] + graph[k][j];
          if (graph[i][j] == -1 || d < graph[i][j]) {
            graph[i][j] = d;
            next[i][j] = next[i][k];
          }
        }
      }
    }
  } 
}

int main() {
  int tc;
  eatline() >> tc;
  while (tc--) {
    int N;
    eatline() >> N;
    map<string, int> loc_to_index;
    vector<string> index_to_loc;
    eatline();
    for (int i=0;i<N;++i) {
      string loc; 
      SS >> loc;
      loc_to_index[loc] = i;
      index_to_loc.push_back(loc);
    }
    vector<vector<int>> graph(N, vector<int>(N, -1));
    vector<vector<int>> next(N, vector<int>(N, -1));
    for (int i=0;i<N;++i) {
      eatline();
      next[i][i] = i;
      for (int j=0;j<N;++j) {
        SS >> graph[i][j];
        next[i][j] = j;
      }
    }

    Floyd(graph, next);

    int Q;
    eatline() >> Q;
    while (Q--) {
      string person, src, dst;
      eatline() >> person >> src >> dst;

      int u = loc_to_index[src], v = loc_to_index[dst];
      int d = graph[u][v];

      if (d == -1) {
        cout << "Sorry Mr " << person << " you can not go from " << src << " to " << dst << endl;
      } else {
        cout << "Mr " << person << " to go from " << src << " to " << dst 
             << ", you will receive " << d << " euros" << endl;
        cout << "Path:" << src;

        vector<int> path;
        int x = next[u][v];
        while (x != v) {
          path.push_back(x);
          x = next[x][v];
        }
        path.push_back(x);

        for (int p : path) {
          cout << " " << index_to_loc[p];
        }
        cout << endl;
      }
    }
  }
}
