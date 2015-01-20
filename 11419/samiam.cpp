#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int R, C, N;

typedef vector<set<int>> Graph;
typedef vector<int> IntList;
typedef vector<bool> BoolList;
typedef set<int> IntSet;

bool dfs(const Graph& g, IntList& m_r, IntList& m_c, BoolList& v_c, int row) {
  for (const int& col : g[row]) {
    if (!v_c[col]) {
      v_c[col] = true;
      if (m_c[col] == -1 || dfs(g, m_r, m_c, v_c, m_c[col])) {
        m_c[col] = row;
        m_r[row] = col;
        return true;
      }
    }
  }
  return false;
}

void dfs2(const Graph& g, // const InitList& m_r,
    const IntList& m_c,
    IntSet& rc, IntSet& cc, int row) {
  rc.erase(row);
  for (const int& col : g[row]) {
    if (cc.count(col) == 0) {
      cc.insert(col);
      dfs2(g, m_c, rc, cc, m_c[col]);
    }
  } 
}

int bi_match(const Graph& g, IntSet& rc, IntSet& cc) {
  IntList m_r(R, -1);
  IntList m_c(C, -1);
  int matches = 0;
  for (int r = 0; r < R; ++r) {
    if (m_r[r] == -1) {
      BoolList v_c(C, false);
      if (dfs(g, m_r, m_c, v_c, r)) {
        matches++;
      }
    }
  }
  
  // Init rc
  for (int r = 0; r < R; ++r) {
    rc.insert(r);
  }
  // Get vertex cover
  for (int r = 0; r < R; ++r) {
    if (m_r[r] == -1) {
      dfs2(g, m_c, rc, cc, r);
    }
  }
  return matches;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> R >> C >> N;
    if (R == 0 && C == 0 && N == 0) 
      break;
    Graph g(R, set<int>());
    for (int n = 0; n < N; ++n) {
      getline(cin, line);
      stringstream ss(line);
      int r, c;
      ss >> r >> c;
      r--; c--;  // row, col should be 0-based index.
      g[r].insert(c);
    }
    getline(cin, line);  // eat blank line.
    IntSet rc, cc;  // row cannons and column cannons
    cout << bi_match(g, rc, cc);
    for (const int& cannon : rc) {
      cout << " r" << cannon + 1;
    }
    for (const int& cannon : cc) {
      cout << " c" << cannon + 1;
    }
    cout << endl;
  }
}
