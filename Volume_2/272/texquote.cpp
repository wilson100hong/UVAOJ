#include <iostream>
using namespace std;
int main() {
  string line;
  bool left = true;
  while(getline(cin, line)) {
    for (int i = 0; i < line.length(); ++i) {
      char c = line [i];
      if (c == '\"') {
        if (left) {
          cout << "``";  
        } else {
          cout << "\'\'";          
        }
        left = !left;
      } else {
        cout << c;  
      }
    }
    cout << endl;
  }


  return 0;
}
