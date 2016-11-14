#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

// 2016/11/12
// STAR: ***
// SKILL: fibonacci numbers
// TRAP: 1) size_t is unsigned, which break negative number check
//       2) '2' at 2th digit is special
//       3) output can be 0

int max(int a, int b) {
  return a > b ? a : b;
}

void solve(const string& s1, const string& s2) {
  // F(n+2) = S(n)
  int n = max(s1.size(), s2.size()) + 5;
  int n1 = s1.size(), n2 = s2.size();
  vector<int> res(n, 0);  // result is the reverse
  for (int i=0;i<res.size();i++) {
    int b1 = n1 >= i+1 ? s1[n1-i-1]-'0':0;
    int b2 = n2 >= i+1 ? s2[n2-i-1]-'0':0;
    res[i] = b1+b2;
  }

  // reduce result with these rules:
  // 1. 011 -> 100
  // 2. 0200 -> 1001
  //    BUT!, if '2' is at 2th digit, 0200 -> 1010
  // 3. 0201 -> 1002, the reduce using 2.
  int cur = 0; 
  while (cur < res.size()) {
    if (res[cur] == 0) {
      cur++;
    } else if (res[cur] == 1) {
      // look ahead
      if (cur+1 < res.size() && res[cur+1] > 0) {
        if (cur+2 >= res.size()) {
          cout << "OUT OF BOUND #1 " << cur+2 << endl;
          exit(1);
        }
        res[cur+2]++;
        res[cur+1]--;
        res[cur] = 0;
      }
      cur++;
    } else {  // res[cur] > 1
      if (cur+1 >= res.size()) {
        cout << "OUT OF BOUND #2 " << cur+2 << endl;
      }
      res[cur+1]++;
      res[cur]-=2;
      if (cur-2 >= 0) {
        res[cur-2]++;
      } else if (cur-2 == -1) {
        res[0]++;
      }
      cur = max(cur-3, 0);
    }
  }
  
  cur = res.size() -1;
  while (res[cur]==0 && cur >= 0) {
    cur--;
  }
  if (cur < 0) {
    // result is 0
    cout << "0";
  } else {
    while (cur >= 0) {
      cout << to_string(res[cur]);
      cur--;
    }
  }
}

int main() {
  string line1, line2, blank;
  bool first = true; 

  while (getline(cin, line1)) {
    getline(cin, line2);
    getline(cin, blank);  // blank line
    if (!first) {
      cout << endl;
    }
    first = false;
    solve(line1, line2);
    cout << endl;
  }
}
