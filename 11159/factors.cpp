// NOTE: be aware of '0': 
//   - 0 can be any number's multiple
//   - but no number can be 0's multiple, except 0
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int N, M;
typedef vector<set<int>> Graph;
typedef vector<int> Vi;
typedef vector<bool> Vb;

bool dfs(const Graph& graph, Vi& m_a, Vi& m_b, Vb& v_b, int n) {
  for (const int& m : graph[n]) {
    if (!v_b[m]) {
      v_b[m] = true;
      if (m_b[m] == -1 || dfs(graph, m_a, m_b, v_b, m_b[m])) {
        m_b[m] = n;
        m_a[n] = m;
        return true;
      }
    }
  }
  return false;
}

int bi_match(const Graph& graph) {
  Vi m_a(N, -1);
  Vi m_b(M, -1); 
  int matches = 0;
  for (int n = 0; n < N; ++n) {
    Vb v_b(M, false);
    if (m_a[n] == -1 && dfs(graph, m_a, m_b, v_b, n)) {
        matches++;
    }
  }
  return matches;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> N;
    Vi aa(N, 0);
    Graph graph(N, set<int>());
    for (int n = 0; n < N; ++n) {
      cin >> aa[n];
    }
    cin >> M;
    Vi bb(M, 0);
    for (int m = 0; m < M; ++m) {
      cin >> bb[m];
      for (int n = 0; n < N; ++n) {
        // NOTE: 4 cases:
        // ( a,  b)   is multiple?
        // -----------------------
        // ( 0,  0)   true
        // (!0,  0)   true 
        // ( 0, !0)   false 
        // (!0, !0)   % == 0 ?
        if (bb[m] == 0 ||
            (aa[n] != 0 && bb[m] % aa[n] == 0)) {
          graph[n].insert(m);
        }
      }
    }
    cout << "Case " << t << ": " <<  bi_match(graph) << endl;
  }
}

