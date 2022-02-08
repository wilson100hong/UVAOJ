// If you use common longest sequence DP algorithm, which is O(n^2), you will get TLE
// 
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int binary_search(const vector<int>& a, int l, int r, int x) {
  // find rightmost index where a[index] < x 
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (a[m] >= x) {
      r = m -1;
    } else {
      l = m;
    }
  }

  if (r > l && a[r] < x) return r;
  return l;
}

// Longest increasing subsequence
int LIS(const vector<int>& a) {
  int n = a.size();
  vector<int> lis(n+1, -1);
  int left= 0, right = 0;
  for (int x: a) {
    // binary search
    int len = binary_search(lis, left, right, x);
    len++;
    lis[len] = x;
    if (len > right) right = len;
  }
  return right;
}

int solve(const vector<int>& first, const vector<int>& second) {
  map<int, int> second_map;
  int n = first.size(), m = second.size();
  for (int i=0;i<m;++i) {
    second_map[second[i]] = i;
  }

  vector<int> a;
  for (int i=0;i<n;++i) {
    int x = first[i];
    if (second_map.count(x)) {
      a.push_back(second_map[x]);
    }
  }
  return LIS(a);
}

int main() {
  int T;
  cin >> T;
  for (int t=1;t<=T;++t) {
    int N, P, Q;
    cin >> N >> P >> Q;
    vector<int> first;
    vector<int> second;
    for (int i=0;i<P+1;++i) {
      int x;
      cin >> x;
      first.push_back(x);
    }
    for (int i=0;i<Q+1;++i) {
      int x;
      cin >> x;
      second.push_back(x);
    }
    cout << "Case " << t << ": " << solve(first, second) << endl;
  }
}
