#include <iostream>
using namespace std;

int abs(int n) {
  return n > 0 ? n : -n;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "0")
      break;
    
    int even = 0, odd = 0;
    for (int i = 0; i < line.length(); ++i) {
      if (i % 2 ==0) {
        even += (line[i] - '0');          
      } else {
        odd += (line[i] - '0');
      }
    }
    string yes = (abs(even - odd) % 11 == 0 ? "" : "not "); 
    cout << line << " is " << yes << "a multiple of 11." << endl;
  }
  return 0;
}
