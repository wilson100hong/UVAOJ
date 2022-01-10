#include <iostream>
#include <sstream>
using namespace std;

void eatline(stringstream& ss) {
  string line;
  getline(cin, line);
  ss.clear();  // important. stringstream has sate at EOF
  ss.str(line);
}

int main() {
  stringstream ss;
  eatline(ss);
  int T;
  ss >> T;
  int sum = 0;
  while (T--) {
    stringstream ss;
    eatline(ss);
    string op;
    ss >> op;
    if (op == "report") {
      cout << sum << endl;
    } else {  // "donate"
      int donate;
      ss >> donate;
      sum += donate;
    }
  }
}
