#include <iostream>
using namespace std;

int main () {
 
  int height, kittens;
  while (cin >> height >> kittens) {
    if (height == 0 && kittens == 0)
      break;
    // height = (m + 1) ^x;
    // kittens = m ^ x;
    
    int m = 1;
    while (m <= height) {
      unsigned long long stack_height = 0;
      unsigned long long free_kittens = 0;
      
      unsigned long long h_pow = 1;
      unsigned long long k_pow = 1;
      while (h_pow < height) {
        free_kittens += k_pow;
        stack_height += (k_pow * (height / h_pow) );
        k_pow *= m;
        h_pow *= (m + 1);
      }
      if (h_pow == height && k_pow == kittens) {
        stack_height += kittens;
        cout << free_kittens << " " << stack_height << endl;
        break;
      }
      m++;
    }
     
  }
  return 0;
}
