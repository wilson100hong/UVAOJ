#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};

int str2int(const string& line) {
  int tmp;
  stringstream ss(line);
  ss >> tmp;
  return tmp;
}

vector<Edge> ParseEdges(int num) {
  string line;
  Edge edge;
  vector<Edge> result;
  for (int i = 0; i < num; ++i) {
    getline(cin, line);
    stringstream ss(line);
    ss >> edge.from >> edge.to >> edge.cost;
    result.push_back(edge);
  }
  return result;
}

typedef map<int, map<int, int> > Graph;
typedef pair<int, int> II;

void MergeWires(const vector<Edge>& wires, Graph& result) {
  for (vector<Edge>::const_iterator it = wires.begin(); it != wires.end(); ++it) {
    if (result.count(it->from) == 0) {
      result[it->from] = map<int, int>();
    }
    if (result.count(it->to) == 0) {
      result[it->to] = map<int, int>();
    }
    result[it->from][it->to] = result[it->to][it->from] = it->cost;
  }
}

int main() {
  string line;
  int N, K, M, from, to, cost;
  int first = true;
  while (getline(cin, line)) {
    if (!first)  {
      getline(cin, line);
    }
    N = str2int(line);
    vector<Edge> current_choice = ParseEdges(N - 1);
    int total = 0;
    for (int i = 0; i < current_choice.size(); ++i) {
      total += current_choice[i].cost;
    }

    if (!first) {
      cout << endl;
    }
    cout << total << endl;

    getline(cin, line);
    K = str2int(line);
    vector<Edge> new_wires = ParseEdges(K);

    getline(cin, line);
    M = str2int(line);
    vector<Edge> old_wires = ParseEdges(M);

    // 1. Combine old_wires with new_wires
    Graph graph;
    MergeWires(old_wires, graph);
    MergeWires(new_wires, graph);

    // 2. Prim's algorithm
    set<II> Q;
    Q.insert(II(0, 1));  // start from node 1
    map<int, int> costs;
    costs[1] = 0;
    set<int> selected;

    while (!Q.empty()) {
      II head = *(Q.begin());
      Q.erase(head);
      int node = head.second;
      selected.insert(node);
      for (map<int, int>::const_iterator it = graph[node].begin(); it != graph[node].end(); ++it) {
        int next = it->first;
        if (selected.count(next) != 0) {
          continue;
        }
        int cost = it->second;
        if (costs.count(next) == 0 || costs[next] > cost) {
          if (costs.count(next) != 0) 
            Q.erase(II(costs[next], next));
          Q.insert(II(cost, next));
          costs[next] = cost;
        }
      }
    }

    total = 0;
    for (map<int, int>::const_iterator it = costs.begin(); it != costs.end(); ++it) {
      total += it->second;
    }
    cout << total << endl;
    first = false;
  }
}
