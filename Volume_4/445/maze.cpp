#include <iostream>
using namespace std;
int main() {
  string line;
  while (getline(cin, line)) {
    int index = 0;
    int sum = 0;  
    while (index < line.length()) {
      char c = line[index];
      if (c == '!') {
        cout << endl;
        sum = 0;
      } else if ('0' <= c && c <= '9') { 
        sum = sum + (c - '0'); 
      } else if (c == 'b') {
        while (sum > 0) {
          cout << " ";
          --sum;
        }
      } else {
        while (sum > 0) {
          cout << c;
          --sum;  
        }
      }
      index++;
    }
    cout << endl;
  }
  return 0;
}
