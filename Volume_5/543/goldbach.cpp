#include <iostream>
#include <cmath>
using namespace std;
#define MAX_N 1000000

bool prime[MAX_N];

void init() {
  for (int i = 0; i < MAX_N; ++i)
    prime[i] = true;
  
  int sq = (int) sqrt(MAX_N) + 1;
  for (int i = 2; i < sq; ++i) {
    if (prime[i]) {
      int j = i * 2;
      while (j < MAX_N) {
        prime[j] = false;
        j += i;
      }  
    }
  }
}


int main() {
  int n;
  init();
  while (cin >> n) {
    if (n == 0)
      break;
    int ok = false;
    for (int i = 2; i < MAX_N; ++i) {
      if (prime[i] && prime[n - i]) {
        ok = true;
        cout << n << " = " << i << " + " << n - i << endl;
        break;
      }
    }
    if (!ok) {
      cout << "Goldbach's conjecture is wrong." << endl;
    }
 }

  return 0;

}
