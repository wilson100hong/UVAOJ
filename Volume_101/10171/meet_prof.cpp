// 2016/10/08
// SKILL: floyd warshall
// STAR: *
// TRAP: 1) more than one place to meet
//       2) multi edges between city
//       3) edge's from != edge'to
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <limits>
using namespace std;
map<char, int> AGE = {{'Y', 0}, {'M', 1}};
typedef vector<vector<int>> Graph;

int MAX = numeric_limits<int>::max() / 8;  // avoid overflow

void solve(vector<Graph>& graphs, int me, int prof) {
  for (int m=0;m<2; ++m) {
    for (int k=0;k<26;++k) {
      for (int i=0;i<26;++i) {
        for (int j=0;j<26;++j) {
          if (graphs[m][i][j] > graphs[m][i][k] + graphs[m][k][j]) {
            graphs[m][i][j] = graphs[m][i][k] + graphs[m][k][j];
          }
        }
      }
    }
  }

  int best = MAX;
  for (int k=0;k<26;++k) {
    if (graphs[0][me][k] + graphs[1][prof][k] < best) {
      best = graphs[0][me][k] + graphs[1][prof][k];
    }
  }
  if (best == MAX) {
    cout << "You will never meet." << endl;
    return;
  }

  cout << best;
  for (int k=0;k<26;++k) {
    if (graphs[0][me][k] + graphs[1][prof][k] == best) {
      cout << " " << static_cast<char>('A'+k);
    }
  }
  cout << endl;
}

int main() {
  
  while (1) {
    int N;
    cin >> N;
    if (N == 0) break;
    
    vector<Graph> graphs(2, Graph(26, vector<int>(26, MAX)));
    for (int i=0;i<26;++i) {
      graphs[0][i][i] = graphs[1][i][i] = 0;
    }

    for (int i=0;i<N;++i) {
      char a, b, c, d;
      cin >> a >> b >> c >> d;
      int cost;
      cin >> cost;
      int from = c-'A', to = d-'A';
      int m = AGE[a];
      if (cost < graphs[m][from][to]) {
        graphs[m][from][to] = cost;
        if (b == 'B' && cost < graphs[m][to][from]) {
          graphs[m][to][from] = cost;
        }
      }
    }
    char me, prof;
    cin >> me >> prof;
    solve(graphs, me-'A', prof-'A');
  }
}
