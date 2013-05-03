#include <iostream>
using namespace std;
int main () {
  string mapping = "22233344455566677778889999";
  string line;
  while (getline(cin, line)) {
    for (int i = 0; i < line.length(); ++i) {
      if ('A' <= line[i] && line[i] <= 'Z') {
        line[i] = mapping[line[i] - 'A'];
      }
    }
    cout << line << endl;
  }
  return 0;
}
