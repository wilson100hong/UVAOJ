#include <iostream>
using namespace std;

int hex(int n) {
  int sum = 0;
  int base = 1;
  while (n > 0) {
    sum += (n % 10) * base;
    n /= 10;
    base *= 16;
  }  
  return sum;
}

int b(int n) {
  int cnt = 0;
  while (n != 0) {
    n &= (n - 1);
    cnt++;  
  }
  return cnt;
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds-- > 0) {
    int n;
    cin >> n;
    int hn = hex(n);
    cout << b(n) << " " << b(hn) << endl;
  }

  return 0;
}
