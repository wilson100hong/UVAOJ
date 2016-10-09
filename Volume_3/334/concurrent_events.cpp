#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <utility>
using namespace std;

// 2016/10/09
// SKILL: floyd warshall. concurrent events means both events are each other's ancestor.
// STAR: **
// TRAP:
set<pair<int, int>> solve(map<int, set<int>>& graph) {
  int n = graph.size();
  // build graph
  vector<vector<bool>> ancestor(n, vector<bool>(n, false));
  for (int i=0;i<n;++i) {
    ancestor[i][i] = true;
  }
  for (auto& kv : graph) {
    int u = kv.first;
    for (int v : kv.second) {
      ancestor[u][v] = true;
    }
  }

  // floyd warshall
  for (int k=0;k<n;++k) {
    for (int i=0;i<n;++i) {
      for (int j=0;j<n;++j) {
        if (ancestor[i][k] && ancestor[k][j]) {
          ancestor[i][j] = true;
        }
      }
    }
  }

  set<pair<int, int>> ans;
  for (int i=0;i<n;++i) {
    for (int j=i+1;j<n;++j) {
      if (!ancestor[i][j] && !ancestor[j][i]) {
        ans.insert({i, j});
      }
    }
  }
  return ans;
}

int main() {
  int NC, NE, NM;
  string event, event2;
  int cases = 1;
  while (cin >> NC) {
    map<string, int> name2id;
    vector<string> id2name;
    map<int, set<int>> graph;
    if (NC==0) break;
    for (int i=0;i<NC;++i) {
      cin >> NE;
      int last_id = -1;
      for (int j=0;j<NE;++j) {
        cin >> event;
        if (name2id.count(event) == 0) {
          int id = id2name.size();
          id2name.push_back(event);
          name2id[event] = id;
          graph[id] = set<int>();
        }
        int id = name2id[event];
        if (last_id >= 0) {
          graph[last_id].insert(id);
        }
        last_id = id;
      }
    }
    cin >> NM;
    for (int i=0;i<NM;++i) {
      cin >> event >> event2;
      int id = name2id[event];
      int id2 = name2id[event2];
      graph[id].insert(id2);
    }

    cout << "Case " << cases << ", ";
    set<pair<int, int>> ces = solve(graph);
    if (ces.size() == 0) {
      cout << "no concurrent events.";
    } else {
      cout << ces.size() << " concurrent events:" << endl;
      bool first = true;
      int cnt = 0;
      for (const auto& ce : ces) {
        first = false;
        cout << "(" << id2name[ce.first] << "," << id2name[ce.second] << ") ";
        cnt++;
        if (cnt >= 2) break;
      }
    }
    cout << endl;
    cases++;
  }
}
