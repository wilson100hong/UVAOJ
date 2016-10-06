#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i=1;i<=n;++i) {
    int l, w, h;
    cin >> l >> w >> h;
    cout << "Case " << i << ": ";
    if (l>20 || w>20 || h>20) {
      cout << "bad" << endl;
    } else {
      cout << "good" << endl;
    }
  }
}
