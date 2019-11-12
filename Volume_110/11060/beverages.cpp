#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
using namespace std;


bool eatline(stringstream& ss) {
  ss.clear();
  string line;
  bool ret = static_cast<bool>(getline(cin, line));
  ss.str(line);
  return ret;
}

vector<int> solve(map<int, set<int>>& graph) {
  int N = graph.size();
  vector<int> indegrees(N, 0);
  for (const auto& kv : graph) {
    for (int v : kv.second) {
      indegrees[v]++;
    }
  }

  vector<int> res;
  set<int> done;

  while (done.size() != N) {
    for (int u=0;u<N;++u) {
      if (!done.count(u) && indegrees[u] == 0) {
        res.push_back(u);
        done.insert(u);
        for (int v : graph[u]) {
          indegrees[v]--;
        }
        break;
      }
    }
  }

  return res;
}

int main() {
  stringstream ss;
  int test = 0;
  while (eatline(ss)) {
    int N, M;
    ss >> N;
    map<int, set<int>> graph;
    vector<string> beverages;
    map<string, int> mapping;

    for (int n=0;n<N;++n) {
      eatline(ss);
      string bs;
      ss >> bs;
      int u = beverages.size();
      graph[u] = set<int>();
      mapping[bs] = u;
      beverages.push_back(bs);
    }

    eatline(ss);
    ss >> M;
    for (int m=0;m<M;++m) {
      eatline(ss);
      string bs1, bs2;
      ss >> bs1 >> bs2;  // b1 -> b2
      int u = mapping[bs1], v = mapping[bs2];
      graph[u].insert(v);
    }

    cout << "Case #" << ++test << ": Dilbert should drink beverages in this order:";
    vector<int> orders = solve(graph);
    for (int u : orders) {
      cout << " " << beverages[u];
    }
    cout << "." << endl << endl;
    eatline(ss);
  }
}
