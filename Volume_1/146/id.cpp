#include <iostream>
using namespace std;
int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    int len = line.length();
    if (len < 2) {
      cout << "No Successor" << endl;
      continue;
    } 
    int t = len - 1; // the bit need swap
    while (t > 0 && line[t - 1] >= line[t]) 
      t--;
    if (t == 0) {
      cout << "No Successor" << endl;
      continue; 
    }
    t--;
    int s = len - 1;
    while (s > t && line[s] <= line[t] ) {
      s--;
    }
    if (s == t)
      cout << "this should not happen" << endl;
    // swap s and t 
    char tmp;
    tmp = line[s];
    line[s] = line[t];
    line[t] = tmp;

    // revese line[t + 1] to line[len - 1]
    s = len - 1;
    t++;
    while (t < s) {
      tmp = line[s];
      line[s] = line[t];
      line[t] = tmp;
      t++;
      s--;
    } 

    cout << line << endl;

  }
  
  return 0;  
}
