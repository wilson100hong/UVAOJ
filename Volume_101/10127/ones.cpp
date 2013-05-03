#include <iostream>
using namespace std;

// f % 10 == r, where f is n * x + d 
int f(int n, int d, int r) {
  while(d % 10 != r) {
    d += n;
  }
  return d;
}


int main() {
  int n;
  while (cin >> n) {
    int cnt = 1;
    int sum = n;
    while (sum != 1) {
      sum = f(n, sum, 1);
      sum /= 10;
      cnt++;
    }
    cout << cnt << endl;
  }

  return 0;
}
