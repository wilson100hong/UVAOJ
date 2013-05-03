#include <iostream>
#include <cmath>
using namespace std;
int main() {
  unsigned int n;
  while (cin >> n) {
    if (n == 0) {
      break;  
    }
    if (n == 1) {
        cout << "yes" << endl;  
    } else {
      unsigned int x = (unsigned int) sqrt( (float)n);
      if (x * x == n) {
        cout << "yes" << endl;
      } else {
        cout << "no" << endl;  
      }
    }
  }

  return 0;
}
