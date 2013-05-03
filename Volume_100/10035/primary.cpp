#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main() {
  unsigned int a, b;
  stringstream ss;
  while (cin >> a >> b) {
    cout << ss.str();
    ss.str("");
    ss.clear();
    int carry = 0;
    int c = 0;
    while (a + b != 0) {
      if (a % 10 + b % 10 + c >= 10) {
        carry++;
        c = 1;
      } else {
        c = 0;
      }
      a = a / 10;
      b = b / 10;
    }
    if (carry == 0)  {
      ss <<  "No carry operation." << endl; 
    } else if (carry == 1) {
      ss <<  carry << " carry operation." << endl;  
    } else {
      ss <<  carry << " carry operations." << endl;
    }
  }
  return 0;
}
