#include <iostream>
using namespace std;
#define MAX_N 1000000
int cnt[MAX_N];

int cyclelen(unsigned int n) {
  if (n < MAX_N && cnt[n] > -1) 
    return cnt[n];
  // n has not been seen before;
  unsigned int nextLen;
  if (n % 2 == 1) {
    nextLen = cyclelen(3*n + 1);
  } else {
    nextLen = cyclelen(n / 2);
  }
  nextLen++;
  if (n < MAX_N)
    cnt[n] = nextLen;
  return nextLen;
}

int acker(unsigned int n) {
  if (n == 1)
    return 3;
  else
    return cyclelen(n);
}

int main() {
  for (int i = 0; i < MAX_N; i++) {
    cnt[i] = -1;
  }
  cnt[1] = 0;
  unsigned int l, h;
  while (cin >> l >> h) {
    if (l == h && h == 0)
      break;
    if (l > h) {
      unsigned int tmp = l;
      l = h;
      h = tmp;
    }
    
    int max = -1;
    unsigned int max_i = -1;
    for (unsigned int i = l; i<= h; i++){
      int len = acker(i);
      if (len > max) {
        max_i = i;
        max = len;
      }
    }
    cout << "Between " << l <<  " and " << h << ", " 
    << max_i << " generates the longest sequence of " << max <<" values."
    << endl;
  }
  return 0;
}


