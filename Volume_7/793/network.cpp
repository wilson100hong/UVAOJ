#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int getline_int() {
  int n;
  string line;
  getline(cin, line);
  stringstream ss(line);
  ss >> n;
  return n;
}

int label(vector<int>& p, int u) {
  if (p[u] != u) {
    p[u] = label(p, p[u]);
  }
  return p[u];
}

void join(vector<int>& p, int u, int v) {
  p[label(p, u)] = p[label(p, v)];
}

int main() {
  int round = getline_int();
  getline_int();  // blank line
  string line;
  bool first = true;
  while (round-- > 0) {
    int n = getline_int();
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {  // 1-based index
      p[i] = i;
    }
    int yes = 0, no = 0;
    while (1) {
      getline(cin, line);
      if (line == "") {
        break;
      }
      auto ss = stringstream(line);
      char type;
      int u, v;
      ss >> type >> u >> v;
      if (type == 'c') {
        join(p, u, v);
      } else if (type == 'q') {
        if (label(p, u) == label(p, v)) {
          yes++;
        } else {
          no++;
        }
      }
    }
    if (!first) {
      cout << endl;
    } else {
      first = false;
    }
    cout << yes << "," << no << endl;
  }
}

