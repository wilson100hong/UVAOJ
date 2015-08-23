// The count-down is not wrapping: 2->1->0->9 is not valid.
#include <iostream>
#include <vector>
using namespace std;

vector<string> DIGIT = {
  "YYYYYYN",  // 0
  "NYYNNNN",
  "YYNYYNY",
  "YYYYNNY",
  "NYYNNYY",
  "YNYYNYY",
  "YNYYYYY",
  "YYYNNNN",
  "YYYYYYY",
  "YYYYNYY"
};

bool valid(string input,  int guess, vector<bool>& broken) {
  if (guess < 0) {
    return false;
  }
  string d = DIGIT[guess];
  for (int i = 0; i < 7; ++i) {
    if (broken[i]) {
      if (input[i] == 'Y') {
        return false;
      }
    } else if (d[i] != input[i]) {
      if (d[i] == 'N') {  // input[i] == 'Y'
        return false;
      } else {
        broken[i] = true;
      }
    }
  }
  return true;
}

bool rec(const vector<string>& inputs, int inputs_index,
         int guess_digit, vector<bool>& broken) {
  if (inputs_index >= inputs.size()) {
    return true;
  }
  if (!valid(inputs[inputs_index], guess_digit, broken)) {
    return false;
  }
  return rec(inputs, inputs_index + 1, guess_digit - 1, broken);
}

bool solve(const vector<string>& inputs) {
  for (int i = 0; i < 10; ++i) {
    vector<bool> broken(7, false);
    if (rec(inputs, 0, i, broken)) {
      return true;
    }
  }
  return false;
}

int main() {
  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;
    vector<string> inputs;
    for (int i = 0; i < n; ++i) {
      string str;
      cin >> str;
      inputs.push_back(str);
    }
    cout << (solve(inputs) ? "MATCH" : "MISMATCH") << endl;
  }
}
