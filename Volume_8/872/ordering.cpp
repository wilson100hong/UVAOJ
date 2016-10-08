// 2016/10/08
// SKILL: graph, ordering, degree
// STAR: *
// TRAP: alphabetical sorting. u->v if u<v
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
using namespace std;

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

bool rec(map<char, set<char>>& graph,
         set<char>& candiates, 
         map<char, int>& indeg,
         vector<char>& seq) {
  int n = graph.size();
  if (seq.size() == n) {
    for (int i=0;i<n;++i) {
      if (i!=0) cout << " ";
      cout << seq[i];
    }
    cout << endl;
    return true;
  }
  bool ok = false;
  for (char u : candiates) {
    map<char, int> indeg_copy(indeg);
    set<char> candiates_copy(candiates);
    vector<char> seq_copy(seq);
    candiates_copy.erase(u);
    for (int v : graph[u]) {
      indeg_copy[v]--;
      if (indeg_copy[v] == 0) {
        candiates_copy.insert(v);
      }
    }
    seq_copy.push_back(u);
    ok |= rec(graph, candiates_copy, indeg_copy, seq_copy);
  }
  return ok;
}

void solve(map<char, set<char>>& graph,
           map<char, int>& indeg) {
  set<char> candiates;
  for (auto& kv : indeg) {
    if (kv.second == 0) {
      candiates.insert(kv.first);
    }
  }

  vector<char> seq;
  bool ok = rec(graph, candiates, indeg, seq);
  if (!ok) {
    cout << "NO" << endl;
  }
}

int main() {
  int cases;
  char letter;
  eatline() >> cases;
  eatline(); // blank line
  bool first = true;
  while (cases--) {
    map<char, set<char>> graph;
    map<char, int> indeg;
    stringstream& ss = eatline();
    while (ss >> letter) {
      graph[letter] = set<char>();
      indeg[letter] = 0;
    }
    stringstream& ss2 = eatline();
    string equation;
    while (ss2 >> equation) {
      char small, big;
      small = equation[0];
      big = equation[2];
      graph[small].insert(big);
      indeg[big]++;
    }
    if (!first) cout << endl;
    first = false;
    solve(graph, indeg);
    eatline();
  }
}
