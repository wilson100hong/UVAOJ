// 2016/10/06
// STAR: *
// SKILL: graph, SCC
// TRAP: 1) when reading inputs, create node for all letters!
//       2) in each set, ordered by 'least' element
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

map<char, set<char>> rev_graph(const map<char, set<char>>& G) {
  map<char, set<char>> RG;
  for (auto& kv : G) {

    // u->v becomes v->u
    char u = kv.first;
    if (RG.count(u) == 0) {
      RG[u] = set<char>();
    }
    for (char v : kv.second) {
      if (RG.count(v) == 0) {
        RG[v] = set<char>();
      }
      RG[v].insert(u);
    }
  }
  return RG;
}

void dfs1(const map<char, set<char>>& graph,
    char u, int& label, map<char, int>& post) {
  post[u] = -1;  // whatever number
  for (char v : graph.at(u)) {
    if (post.count(v) == 0) {
      dfs1(graph, v, label, post);
    }
  }
  post[u] = label++;
}

void dfs2(const map<char, set<char>>& graph,
    char u, int color, map<char, int>& colors) {
  colors[u] = color;  // whatever number
  for (char v : graph.at(u)) {
    if (colors.count(v) == 0) {
      dfs2(graph, v, color, colors);
    }
  }
}

vector<set<char>> solve(const map<char, set<char>>& graph) {
  // build rev_graph
  map<char, set<char>> rg = rev_graph(graph);

  map<char, int> post;
  int label = 0;
  for (auto& kv : graph) {
    char u = kv.first;
    if (post.count(u) == 0) {
      dfs1(rg, u, label, post);
    }
  }

  // sort
  set<pair<int, char>> order;
  for (const auto& kv: post) {
    order.insert({kv.second, kv.first});
  }

  map<char, int> colors;
  int color = 0;
  for (auto it=order.rbegin(); it!=order.rend();++it) {
    char u = it->second;
    if (colors.count(u) == 0) {
      dfs2(graph, u, color, colors);
      color++;
    }
  }
  vector<set<char>> groups(color, set<char>());
  for (auto& kv : colors) {
    groups[kv.second].insert(kv.first);
  }
  return groups;
}


int main() {
  int N;
  char letter;
  bool first_case = true;
  while (cin >> N) {
    if (N==0) break;
    map<char, set<char>> graph;
    // u->v edge if u beat v
    for (int i=0;i<N;++i) {
      set<char> losers;
      for (int j=0;j<5;++j) {
        cin >> letter;
        if (graph.count(letter) == 0) {
          graph[letter] = set<char>();
        }
        losers.insert(letter);
      }
      cin >> letter;
      if (graph.count(letter) == 0) {
        graph[letter] = set<char>();
      }
      graph[letter].insert(losers.begin(), losers.end());
    }
    vector<set<char>> groups = solve(graph);
    sort(groups.begin(), groups.end());

    if (!first_case) {
      cout << endl;
    }
    first_case = false;

    for (const auto& g : groups) {
      bool first = true;
      for (char c : g) {
        if (!first) cout << " ";
        first = false;
        cout << c;
      }
      cout << endl;
    }
  }
}
