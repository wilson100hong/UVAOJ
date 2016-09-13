// NOTE:
// 1. be careful for the while loop termination condition for '(',
//    should be paired ')'
#include <iostream>
#include <stack>
using namespace std;

int pr(char c) {  // precedence
  if (c == '(') return 0;
  if (c == ')') return 1;
  if (c == '+' || c == '-') return 2;
  if (c == '*' || c == '/') return 3;
  return -1;  // should never happen
}

int main() {
  int cases;
  bool first = true;
  string line;
  cin >> cases;
  getline(cin, line);
  getline(cin, line);
  while (cases--) {
    stack<char> ops;
    string result;
    while (1) {
      getline(cin, line);
      if (line == "") {
        break;
      }
      char c = line[0];
      if ('0' <= c && c <= '9') {
        result += c;
      } else if (c == '(') {
        ops.push(c);
      } else {
        while (!ops.empty() && pr(ops.top()) >= pr(c)) {
          char poped = ops.top();
          ops.pop();
          result += poped;
        }
        if (c == ')') {
          ops.pop();  // pop '('
        } else {
          ops.push(c);
        }
      }
    }
    while (!ops.empty()) {
      char poped = ops.top();
      ops.pop();
      result += poped;
    }

    if (!first) cout << endl;
    cout << result << endl;
    first = false;
  }
}
