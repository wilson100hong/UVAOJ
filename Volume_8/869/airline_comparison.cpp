#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <utility>
using namespace std;

// 2016/10/09
// SKILL: floyd warshall (maybe overkill?)
// STAR: 
// TRAP: airline is bi-direction..
int main() {
  int cases;
  cin >> cases;
  bool first = true;
  while (cases--) {
    int N, M;
    vector<vector<bool>> airline1(26, vector<bool>(26, false));
    vector<vector<bool>> airline2(26, vector<bool>(26, false));
    for (int i=0;i<26;++i) {
      airline1[i][i] = airline2[i][i] = true;
    }
    cin >> N;
    for (int i=0;i<N;++i) {
      char src, dest;
      cin >> src >> dest;
      int from = src-'A', to=dest-'A';
      airline1[from][to] = true;
      airline1[to][from] = true;
    }
    cin >> M;
    for (int i=0;i<M;++i) {
      char src, dest;
      cin >> src >> dest;
      int from = src-'A', to=dest-'A';
      airline2[from][to] = true;
      airline2[to][from] = true;
    }
    // floyd warshall
    for (int k=0;k<26;++k) {
      for (int i=0;i<26;++i) {
        for (int j =0;j<26;++j) {
          if (airline1[i][k] && airline1[k][j]) {
            airline1[i][j] = true;
          }
          if (airline2[i][k] && airline2[k][j]) {
            airline2[i][j] = true;
          }
        }
      }
    }
    if (!first) cout << endl;
    first = false;
    bool same = true;
    for (int i=0;i<26;++i) {
      for (int j=0;j<26;++j) {
        if (airline1[i][j] != airline2[i][j]) {
          same = false;
          break;
        }
      }
      if (!same) break;
    }
    if (same) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}

