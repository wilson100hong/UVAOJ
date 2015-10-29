#include <iostream>
#include <sstream>

using namespace std;

int decode(const string& line) {
  // |  o  . o | -> 'A'
  string stripped = line.substr(1, 9);
  int code = 0;
  for (int i = 0; i < stripped.size(); ++i) {
    if (stripped[i] == '.') continue;
    code *= 2;
    if (stripped[i] == 'o') {
      code++;
    }
  }
  return code; 
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "___________") continue;
    cout << (char) decode(line);
  }
}
