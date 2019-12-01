// NOTE: there could be bi-direction capacity for the same edge
// u->v = c1
// v->u = c2
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <set>
using namespace std;

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

struct Edge {
  // a-> b
  int cap;
  int flow;
};

typedef vector<map<int, Edge>> Graph;

// Debug usage
void PrintPath(const vector<int>& path) {
  for (int u : path) {
    cout << u << ", ";
  }
  cout << endl;
}

int residue(Graph& graph, vector<bool>& visit, int u, int dst, int flow, vector<int>& path) {
  visit[u] = true;
  path.push_back(u);
  if (u == dst) {
    PrintPath(path);
    path.pop_back();
    return flow;
  }
  for (auto& kv : graph[u]) {
    int v = kv.first;
    if (visit[v]) continue;

    // Update flow on edge
    int rest = max(0, graph[u][v].cap - graph[u][v].flow);
    int new_flow = min(flow, rest);
    if (new_flow <= 0) continue;

    int f = residue(graph, visit, v, dst, new_flow, path);
    if (f > 0) {
      graph[u][v].flow += f;
      graph[v][u].flow -= f;
      return f;
    }
  }
  path.pop_back();
  return 0;
}

int solve(
    const map<string, int>& devices,
    const map<string, int>& receptacles, 
    const map<string, set<string>>& adapters) {
  // |total| is the max flow.
  int total = 0;
  for (const auto& kv : devices) {
    total += kv.second;
  }

  // 1. Build graph
  Graph graph;
  graph.push_back(map<int, Edge>());  // graph[0]: source 
  graph.push_back(map<int, Edge>());  // graph[1]: destination 
  map<string, int> type_to_index;

  // 1.1 Create nodes from source to type 
  for (const auto& kv : devices) {
    const string& type = kv.first;
    if (!type_to_index.count(type)) {
      type_to_index[type] = graph.size();
      graph.push_back(map<int, Edge>());
    }
    int u = type_to_index[type];

    // Link type from source 
    int cnt = kv.second;
    graph[0][u] = {cnt, 0};  // src -> u
    graph[u][0] = {0, 0};
  }

  // 1.2 Create nodes from destination to type
  for (const auto& kv : receptacles) {
    const string& type = kv.first;
    if (!type_to_index.count(type)) {
      type_to_index[type] = graph.size();
      graph.push_back(map<int, Edge>());
    }
    int u = type_to_index[type];

    // Link type to destination
    int cnt = kv.second;
    graph[u][1] = {cnt, 0};  // u -> dest
    graph[1][u] = {0, 0};
  }

  // 1.3 Create nodes for adpaters
  for (const auto& kv : adapters) {
    const string& type1 = kv.first;
    if (!type_to_index.count(type1)) {
      type_to_index[type1] = graph.size();
      graph.push_back(map<int, Edge>());
    }
    int u = type_to_index[type1];

    for (const string& type2 : kv.second) {
      if (!type_to_index.count(type2)) {
        type_to_index[type2] = graph.size();
        graph.push_back(map<int, Edge>());
      }
      int v = type_to_index[type2];
      // u->v
      graph[u][v] = {total, 0};
      graph[v][u] = {max(graph[v][u].cap, 0), 0};
    }
  }

  // 2. Max flow
  int max_flow = 0;
  int n = graph.size();
  while (true) {
    vector<bool> visit(n, false);
    vector<int> path;
    int inc = residue(graph, visit, 0, 1, total, path);
    if (inc == 0) break;
    max_flow += inc;
  }
  return total - max_flow;
}

int main() {
  int T;
  eatline() >> T;
  bool first = true;
  while (T--) {
    eatline();   // blank line
    int N, M, K;

    eatline() >> N;
    map<string, int> receptacles;
    for (int i=0;i<N;++i) {
      string type;
      eatline() >> type;
      receptacles[type]++;
    }

    eatline() >> M;
    map<string, int> devices;
    for (int i=0;i<M;++i) {
      string device, type;
      eatline() >> device >> type;
      devices[type]++;
    }

    eatline() >> K;
    map<string, set<string>> adapters;

    for (int i=0;i<K;++i) {
      string in, out;
      eatline() >> in >> out;
      if (in == out) continue;
      adapters[in].insert(out);
    }

    if (!first) {
      cout << endl;
    }
    first = false;
    cout << solve(devices, receptacles, adapters) << endl;
  }
}
