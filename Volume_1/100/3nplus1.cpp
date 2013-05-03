#include <iostream>
using namespace std;
int cnt[1000000];


int cyclelen(int n) {
  if (n < 1000000 && cnt[n] > 0) {
    return cnt[n];
  }   
  // n has not been seen before;
  int nextLen;
  if (n % 2 == 1) {
    nextLen = cyclelen(3*n + 1);
  } else {
    nextLen = cyclelen(n / 2);
  }
  if ( n < 1000000) {
    cnt[n] = nextLen + 1;
  }
  return nextLen + 1;
}

int max(int a, int b) {
  return a >= b ? a : b;  
}


int main() {
  for (int i = 0; i < 1000000; i++) {
    cnt[i] = 0;
  }
  
  cnt[1] = 1;
  int a, b, c, d;
  while (cin >> a >> b) {
    int max = 0;
    if (a <= b) {
      c = a;
      d = b;
    } else {
      c = b;
      d = a;
    }
    for (int num = c; num<= d; num++){
      int len = cyclelen(num);
      if (len > max) {
        max = len;
      }
    }
    cout << a << " " << b << " " << max << endl;
  }
  return 0;
}


