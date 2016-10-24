#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <sstream>
using namespace std;

// 2016/10/23
// STAR: **
// SKILL: bellmon-ford (or SPFA)
// TRAP: 1) number of stops could > cities
//       2) your bellman-ford is wrong: it update too many nodes at each iteration

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

string START = "Calgary";
string END = "Fredericton";

int MAX = 1e7;

int main() {
  int cases;
  bool first = true;
  eatline() >> cases;
  for (int scene=0;scene<cases;++scene) {
    // read inputs
    eatline(); // blank line
    int n, m;
    eatline() >> n;
    unordered_map<string, unordered_map<string, int>> graph;
    for (int i=0;i<n;++i) {
      string city;
      eatline() >> city;
      graph[city] = unordered_map<string, int>();
    }
    eatline() >> m;
    for (int i=0;i<m;++i) {
      string from, to;
      int cost;
      eatline() >> from >> to >> cost;
      if (!graph[from].count(to) || cost < graph[from][to]) {
        graph[from][to] = cost;
      }
    }
    stringstream& ss = eatline();
    int nq;
    ss >> nq;

    vector<int> query;
    for (int i=0;i<nq;++i) {
      int stop;
      ss >> stop;
      query.push_back(stop);
    }

    unordered_map<string, int> dist;
    dist[START] = 0;

    vector<int> ans(n-1, MAX);
    
    // TODO: bellman-ford wrong. it will update too many nodes in one iteration
    for (int stop=0;stop<n-1;++stop) {
      // cout << endl;
      unordered_map<string, int> new_dist;
      // for all edges
      for (auto& kv : graph) {
        string from = kv.first;
        if (dist.count(from)) {
          for (auto& kv2 : kv.second) {
            string to = kv2.first;
            //cout << "from: " << from << " to: " << to << endl;
            int cost = kv2.second;
            int nd = dist[from] + cost;
            if (!dist.count(to) || nd < dist[to]) {
              if (!new_dist.count(to) || nd < new_dist[to]) {
                new_dist[to] = nd;
              }
            }
          }
        }
      }
      // update new_dist to dist
      for (auto& kv : new_dist) {
        dist[kv.first] = kv.second;  // new_dist must be better than dist
      }

      if (dist.count(END)) {
        ans[stop] =  dist[END];
      } else {
        ans[stop] = MAX;
      }
    }

    if (!first) cout << endl;
    first = false;
    cout << "Scenario #" << scene+1 << endl;
    for (int i=0;i<nq;++i) {
      int spending = (query[i] >= ans.size() ? ans[ans.size()-1] : ans[query[i]]);
      if (spending == MAX) {
        cout << "No satisfactory flights" << endl;
      } else {
        cout << "Total cost of flight(s) is $" << spending << endl;
      }
    }
  }
}
