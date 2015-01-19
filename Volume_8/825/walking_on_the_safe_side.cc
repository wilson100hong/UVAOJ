#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  int T;
  string line;
  getline(cin, line);
  stringstream ss(line);
  ss >> T;

  bool first = true;
  while (T-- > 0) {
    int W, H;
    getline(cin, line);  // blank line
    getline(cin, line);
    stringstream ss(line);
    ss >> H >> W;

    // NOTE: 0-based index
    vector<set<int> > blocks;
    for (int i = 0; i < H; ++i) {
      blocks.push_back(set<int>());
    }
    for (int i = 0; i < H; ++i) {
      getline(cin, line);
      stringstream ss(line);
      int j, b;
      ss >> j;
      j--;
      while (ss >> b) {
        b--;
        blocks[j].insert(b);
      }
    }

    // solve
    vector<int> cnt(W, 0);
    cnt[0] = 1;
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        int left = (j == 0 ? 0 : cnt[j - 1]);
        cnt[j] = (blocks[i].count(j) != 0 ? 0 : cnt[j] + left);
      }
    }
    if (!first) 
      cout << endl;
    cout << cnt[W - 1] << endl;
    first = false;
  }
}
