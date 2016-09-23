#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(const vector<int>& list, int v) {
  int l=0, r=list.size()-1;
  // binary search find the index for first v
  int index = -1;
  while (l <= r) {
    int m = (l+r)/2;
    if (list[m] < v) {
      l = m + 1;
    } else if (list[m] > v) {
      r = m - 1;
    } else {  // list[m] == v
      index = m;
      r = m - 1;
    }
  }
  return index;
}

int main() {
  int N, Q;
  vector<int> marbles;
  int cases = 1;
  while (1) {
    cin >> N >> Q;
    if (N==0 && Q==0) break;
    marbles.clear();
    for (int i=0;i<N;++i) {
      int m;
      cin >> m;
      marbles.push_back(m);
    }
    sort(marbles.begin(), marbles.end());

    cout << "CASE# " << cases << ":" << endl;
    for (int i=0;i<Q;++i) {
      int v;
      cin >> v;
      int index = solve(marbles, v);
      if (index == -1) {
        cout << v << " not found" << endl;
      } else {
        cout << v << " found at " << index+1 << endl;
      }
    }
    cases++;
  }
}
