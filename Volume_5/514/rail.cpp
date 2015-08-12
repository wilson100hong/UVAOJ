#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main() {
  int n;
  bool first = true;
  while (1) {  // loop for all blocks
    cin >> n;
    if (n == 0)
      break;
    while(1) {  // loop for all reorg
      stack<int> stk;
      int tmp;
      cin >> tmp;
      if (tmp == 0) {
        break;
      }
      vector<int> want;
      // 0-indexed
      want.push_back(tmp - 1);
      for (int i = 1; i < n; ++i) {
        cin >> tmp;
        want.push_back(tmp - 1);
      }

      int i = 0, j = 0;
      while (j < n && i <= n) {
        // end of block
        if (!stk.empty() && stk.top() == want[j]) {
          stk.pop();
          j++;
        } else { 
          if (i != want[j]) {
            stk.push(i);
          } else {
            j++;
          }
          i++;
        }
      }
      if (stk.empty()) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
    cout << endl;
  }
}
