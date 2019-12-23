#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

bool BM(const vector<set<int>>& bots, int u, vector<int>& mb, vector<int>& mn, vector<bool>& vn) {
  int B = mb.size();
  int N = mn.size();

  for (int v : bots[u]) {
    if (vn[v]) continue;
    vn[v] = true;
    if (mn[v] == -1
        || BM(bots, mn[v], mb, mn, vn)) {
      mn[v] = u;
      mb[u] = v;
      return true;
    }
  }
  return false;
}

int Solve(const vector<set<int>>& bots, int B, int N) {
  vector<int> mb(B, -1);
  vector<int> mn(N, -1);

  int M = 0;

  for (int u=0;u<B;++u) {
    if (mb[u] == -1) {
      vector<bool> vn(N, false);
      if (BM(bots, u, mb, mn, vn)) {
        M++;
      }
    }
  }

  return M;
}

int main() {
  int T;
  cin >> T;
  for (int t=1;t<=T;++t) {
    int B, N;
    cin >> B >> N;
    vector<set<int>> bots(B, set<int>());

    for (int i=0;i<B;++i) {
      for (int j=0;j<N;++j) {
        int x;
        cin >> x;
        if (x == 1) {
          bots[i].insert(j);
        }
      }
    }

    int ans = Solve(bots, B, N);

    cout << "Case " << t << 
        ": a maximum of " << ans << " nuts and bolts can be fitted together" << endl;
  }
}
