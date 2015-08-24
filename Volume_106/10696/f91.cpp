#include <iostream>
using namespace std;
int f[101] = {0};
int f91(int n) {
  if (n >= 101) {
    return n - 10;  
  } else if (f[n] != 0) {
    return f[n];  
  } else {
    int res = f91(f91(n+11));
    f[n] = res;
    return res;
  }
}
int main() {
  int in;
  while (cin >> in) {
    if (in == 0) {
      break;  
    }
    cout << "f91(" << in << ") = " << f91(in) << endl; 
  }
  return 0;
}
