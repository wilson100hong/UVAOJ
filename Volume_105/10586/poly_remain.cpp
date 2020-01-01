#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef long long LL;

vector<LL> Solve(const vector<LL>& as, const vector<LL>& ds) {
  int K = ds.size(), N = as.size();
  vector<LL> rs(as);
  for (int i=0; N-i >= K; ++i) {
    if (rs[i] == 0) continue;
    LL q = rs[i];
    for (int j=0;j<K;++j) {
      rs[i+j] -= q*ds[j];
    }
  }

  // Remove leading zeros.
  int z = 0;
  while (z < rs.size() && rs[z] == 0) {
    z++;
  }
  if (z >= N) {
    return vector<LL>();
  }
  return vector<LL>(rs.begin() + z, rs.end()); 
}

int main() {
  int N, K;
  while (cin >> N >> K) {
    // [0]: x^N
    vector<LL> as(N+1, 0);
    if (N == -1 && K == -1) break;
    for (int i=0;i<=N;++i) {
      cin >> as[N-i];
    }
    vector<LL> ds(K+1, 0);
    ds[0] = 1;
    ds[K] = 1;

    vector<LL> ans = Solve(as, ds);

    if (ans.empty()) {
      cout << "0";
    } else {
      bool first = true;
      for (int i=ans.size()-1;i>=0;--i) {
        if (!first) cout << " ";
        first = false;
        cout << ans[i];
      }
    }
    cout << endl;
  }
}
