#include <iostream>
#include <vector>
#include <map>
using namespace std;

bool exists(const std::map<int, long long>& map, const int n) {
    return map.end() != map.find(n);
}

int main() {
  vector<int> order;
  map<int, long long> cnt;
  int n;
  while (cin >> n) {
    if (!exists(cnt, n)) {
      order.push_back(n);
      cnt[n] = 1;
    } else {
      cnt[n] = cnt[n] + 1;
    }
  }
  // dump
  for (int i = 0; i < order.size(); ++i) 
    cout << order[i] << " " << cnt[order[i]] << endl;
}
