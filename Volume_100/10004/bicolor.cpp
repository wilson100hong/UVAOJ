#include <iostream>
using namespace std;

#define MAX_N 200
int edges[MAX_N][MAX_N];
bool color[MAX_N];
bool visit[MAX_N];
int n;
void init() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      edges[i][j] = 0;
    }
    visit[i] = false;
  }
}

void dump() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << edges[i][j];
    }
    cout << endl;
  }  
}

bool coloring(int node, bool isBlack) {
  if (visit[node]) {
    return true;
  }
  bool able  = true;
  for (int j = 0; j < n; ++j) {
    if (edges[node][j] == 1
      && node != j
      && visit[j]
      && color[j] == isBlack) {
      return false;   // cannot coloring
    }  
  }
  // Color this node
  visit[node] = true;
  color[node] = isBlack;
  for (int j = 0; j < n; ++j) {
    if (edges[node][j] == 1
      && node != j
      && !visit[j]) {
        if (coloring(j, !isBlack) == false) {
          return false;  
        } 
      }
    }
  return true;
}

int main() {
  while (cin >> n) {
    init();
    if (n == 0) {
      break;
    }
    int l, u, v;
    cin >> l;
    while (l-- > 0) {
      cin >> u >> v;
      edges[u][v] = 1;
      edges[v][u] = 1;
    }
    
    // test
    // dump();
    bool ok = coloring(0, true);
    if (ok) {
      cout << "BICOLORABLE." << endl;  
    } else {
      cout << "NOT BICOLORABLE." << endl;  
    }
  }
  
  return 0;
}
