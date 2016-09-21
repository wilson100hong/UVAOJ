#include <iostream>
using namespace std;
int main() {
  int T;
  cin >> T;
  for (int t=1; t<=T; ++t) {
    int N;
    cin >> N;
    int prev;
    cin >> prev;
    int hj = 0, lj = 0;
    for (int n=1; n<N; ++n) {
      int cur;
      cin >> cur;
      if (cur > prev) {
        hj++;
      } else if (cur < prev) {
        lj++;
      }
      prev = cur;
    }
    cout << "Case " << t << ": " << hj << " " << lj << endl;
  }

}
