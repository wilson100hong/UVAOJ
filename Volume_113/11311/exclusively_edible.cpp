// 4-pile nim game
#include <iostream>
using namespace std;

string Solve(int m, int n, int r, int c) {
  int piles[4] = {
    r,  // to top
    m-1-r,  // to bottom
    c,
    n-1-c
  };

  int res = 0;
  for (int i=0;i<4;++i) {
    res = res ^ piles[i];
  }

  return res == 0 ? "Hansel": "Gretel";
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int m, n, r, c;
    cin >> m >> n >> r >> c;
    cout << Solve(m, n, r, c) << endl;
  }
}
