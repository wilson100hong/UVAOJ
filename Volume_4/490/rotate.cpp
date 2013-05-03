#include <iostream>
#include <vector>
using namespace std;
int main () {
  vector<string> lines;
  string line;
  int max = -1;
  while (getline(cin, line)) {
    int len = line.length();
    if (len > max)
      max = len;
    lines.push_back(line);
  }

  for (int k = 0; k < max; ++k) {
    for (int i = lines.size() - 1; i >= 0; --i) {
      if (lines[i].length() > k) {
        cout << lines[i][k]; 
      } else {
        cout << " ";
      }
    }
    cout << endl;
  }
  return 0;
}
