#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
using namespace std;

// 2016/10/16
// STAR:
// SKILL: bipartie match
// TRAP:

bool match(const vector<vector<int>>& graph, int x,
    vector<bool>& visit,
    vector<int>& mx,
    vector<int>& my) {
  for (int y : graph[x]) {
    if (!visit[y]) {
      visit[y] = true;
      if (my[y] == -1 || match(graph, my[y], visit, mx, my)) {
        mx[x] = y;
        my[y] = x;
        return true;
      }
    }
  }
  return false;
}

void bimatch(const vector<vector<int>>& graph, int ylen,
    const vector<vector<int>>& c2xs) {  // edge for x->y
  vector<int> mx(graph.size(), -1);
  vector<int> my(ylen, -1);
  int mc=0;
  for (int x=0;x<mx.size();++x) {
    for (int y : graph[x]) {
      if (my[y]==-1) {
        my[y] = x;
        mx[x] = y;
        mc++;
        break;
      }
    }
  }

  for (int x=0;x<mx.size();++x) {
    if (mx[x] == -1) {
      vector<bool> visit(ylen, false);
      if (match(graph, x, visit, mx, my)) {
        mc++;
      }
    }
  }
  if (mc!=graph.size()) {
    cout << 0 << endl;
    return;
  }
  cout << 1 << endl;

  // print output
  for (const auto& xs : c2xs) {
    bool first=true;
    for (int x : xs) {
      if (!first) cout << " ";
      first = false;
      cout << mx[x]+1;
    }
    cout << endl;
  }
}

int main() {
  int nk, np;
  while (cin >> nk >> np) {
    if (nk==0 && np==0) break;
    // 1. build bipartie graph. 0-based
    //    x: (duplicate) category 
    //    y: question
    vector<vector<int>> c2xs;  // 
    vector<vector<int>> graph;  // edge for x->y
    for (int i=0;i<nk;++i) {
      vector<int> xs;
      int k;
      cin >> k;  // duplicate factor
      while (k--) {
        xs.push_back(graph.size());
        graph.push_back(vector<int>());
      }
      c2xs.push_back(xs);
    }
    for (int i=0;i<np;++i) {
      int p;
      cin >> p;
      while (p--) {
        int cat;
        cin >> cat;
        cat--;  // 0 based
        for (int x : c2xs[cat]) {
          graph[x].push_back(i);
        }
      }
    }
    bimatch(graph, np, c2xs);
  }
}
