#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <functional>
using namespace std;

void DFS(map<char, set<char>>& graph, char u, vector<char>& post, set<char>& visit) {
  visit.insert(u);
  //cout << "u: " << u << endl;
  //cout << "v: ";
  //for (char v : graph[u]) {
    //cout << v << ", ";
  //}
  //cout << endl;
  for (char v : graph[u]) {
    if (visit.count(v) == 0) {
      DFS(graph, v, post, visit);
    }
  }
  post.push_back(u);
}

int Solve(map<char, int>& costs, map<char, set<char>>& graph, map<char, set<char>>& rev_graph) {
  // 1. Topological sort
  vector<char> post;
  set<char> visit;
  for (const auto& kv : costs) {
    char u = kv.first;
    if (!visit.count(u)) {
      DFS(graph, u, post, visit);
    }
  }

  //cout << "post: ";
  //for (char u : post) {
    //cout << u << ",";
  //}
  //cout << endl;

  // 2. Longest distance
  map<char, int> dist;
  for (int i=post.size()-1;i>=0;i--) {
    char u = post[i];
    //cout << "ku: " << u << endl;
    int max_cost = 0;
    for (char v : rev_graph[u]) {
      if (dist[v] > max_cost) {
        max_cost = dist[v];
      }
    }
    dist[u] = max_cost + costs[u];
  }
  
  int total = 0;
  for (const auto& kv : dist) {
    if (kv.second > total) {
      total = kv.second;
    }
  }
  return total;
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int tc;
  ss >> tc;
  bool first = true;
  getline(cin, line);
  while (tc--) {
    map<char, int> costs;
    map<char, set<char>> graph;
    map<char, set<char>> rev_graph;

    while (1) {
      getline(cin, line);
      if (line == "") break;
      char u = line[0];
      //cout << "U: " << u << endl;

      int cur = 2;
      int cost = 0;
      while (cur < line.size()) {
        char cc = line[cur++];
        if (cc < '0' || cc > '9') break;
        cost = cost * 10 + (cc - '0');
      }
      costs[u] = cost;

      while (cur < line.size()) {
        char v = line[cur++];
        //cout << "   V: " << v << endl;
        graph[v].insert(u);
        rev_graph[u].insert(v);
      }
    }

    if (!first) cout << endl;
    first = false;
    cout << Solve(costs, graph, rev_graph) << endl;

    // TODO: Solve
    //for (const auto& kv : graph) {
      //cout << kv.first << ": ";
      //for (char v : kv.second) {
        //cout << v << ",";
      //}
      //cout << endl;
    //}
  }
}
