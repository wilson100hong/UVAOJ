#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
  unsigned long int a, b;
  while ( cin >> a >> b) {
     if (a >= b) {
       cout << a - b << endl;  
     } else {
       cout << b - a << endl;  
     }
  }  
  return 0;
}
