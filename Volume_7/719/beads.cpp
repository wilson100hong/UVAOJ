// Minimum expression: http://www.quora.com/How-does-the-minimum-expression-algorithm-by-Zhou-Yuan-work
#include <iostream>
#include <string>
using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}

int solve(const string& str) {
  int n = str.length();
  string s = str + str;  // make string rotation easier 
  int i = 0, j = 1, k = 0;
  while (j < n) {
    if (s[i+k] == s[j+k]) {
      //cout << "first" << endl;
      k++;
      if (k == n) {
        // since j = j + n and j always >= n thus exit the loop
        break;
      }
    } else if (s[i+k] < s[j+k]) {
      // we can skip all j from j ~ j + k.
      // Why? use induction to prove:
      // Support s[i] is the minimal rotation among s[i] to s[j]
      // if there is minimal rotation at s[j+v], where 0 <= v <= k,
      // there must be a corresponding rotation at s[i+v] which has the same prefix as s[j+v], and even smaller.
      // => contradicory. Q.E.D.
      j = j + k + 1;
      k = 0;
    } else {  // s[i+k] > s[j+k]
      // We can either advance j by 1, or pick i + k, with the larger one.
      // Why can we skip s[j] to s[i+k]? similiar to above, if there is a smaller rotation between the range,
      // it will cause contradictory that s[i] is not minimal between s[i] to s[j].
      int tmp = j;
      j = max(j + 1, i + k);
      i = tmp;
      k = 0;
    }
  }
  return i;
}

int main() {
  int round;
  cin >> round;
  while (round-- > 0) {
    string str;
    cin >> str;
    cout << solve(str) + 1 << endl;
  }
}
