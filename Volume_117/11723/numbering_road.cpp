#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  int R, N;
  int case_num = 1;
  while (cin >> R >> N) {
    if (R == 0 && N == 0) break;
    cout << "Case " << case_num++ << ": ";
    int ans;
    if (N >= R) {
      cout << 0;
    } else if (R > N*27) {
      cout << "impossible";
    } else {
      int q = (R - N) / N;
      if (q * N < (R - N)) q++;
      cout << q;
    }
    cout << endl;
  }
}
