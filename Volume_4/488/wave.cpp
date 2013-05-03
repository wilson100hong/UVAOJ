#include <iostream>
using namespace std;
int main() {
  int rounds;
  string line;
  cin >> rounds;
  while (rounds-- > 0) {
    getline(cin, line);
    int a, f;
    cin >> a >> f;
    while(f-- > 0) {
      for (int i = 1; i <= a; ++i) {
        for (int j = 0; j < i; ++j) {
          cout << i;
        }
        cout << endl;
      } 
      for (int i = a - 1; i >= 1; --i) {
        for (int j = 0; j < i; ++j) {
          cout << i;  
        }  
        cout << endl;
      }
      if (f > 0) {
        cout << endl;  
      }  
    }
    if (rounds > 0) {
      cout << endl;
    }
  }
  return 0;

}
