#include <iostream>
#include <cmath>
using namespace std;

int pow10(int n) {
  int a = 1;
  while (n--)
    a *= 10;
  return a;
}

void padding(int half, int a) {
  int b = a;
  if (a == 0)
    b = 1;      
 
  int sum = 10;
  while (sum * b < half) {
    sum*= 10;
    cout << "0";
  }
  cout << a;
  
}


using namespace std;
int main() {
  int n;
  while (cin >> n) {
    int max = pow10(n);
    int half = pow10(n / 2);
    for (int i = 0; i < max; i++) {
      int a = i / half; 
      int b = i % half;
      if ((a + b) * (a + b) ==i) {
        padding(half, a);
        padding(half, b);
        cout << endl;
      }
    }
  }
  return 0;
}
