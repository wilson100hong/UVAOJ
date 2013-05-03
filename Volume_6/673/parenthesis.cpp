#include <iostream>
#include <stack>
using namespace std;

int main() {
  int n;
  cin >> n;
  string input;
  getline(cin, input);
  while (n-- > 0) {
    getline(cin, input);
    stack<char> mystack;
    bool ok = true;
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == '(' || input[i] == '[') {
        mystack.push(input[i]);
      } else {
        if (mystack.empty()) {
          ok = false;
          break;
        }
        char c = mystack.top();
        if ((input[i] == ')' && c == '(') ||
            (input[i] == ']' && c == '[')) {
          mystack.pop();
        } else {
          ok = false;
          break;
        }
      }
    }
    if (!ok) 
      cout << "No" << endl;
    else 
      cout << (mystack.empty() ? "Yes" : "No" ) << endl;
  }
  return 0;
}
