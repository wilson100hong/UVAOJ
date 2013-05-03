#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> primes;
void init() {
  unsigned int max = (1 << 31) - 1;
  int sq = sqrt(max);
  int*p = new int[sq + 1];
  for (int i = 0; i <= sq; ++i) 
    p[i] = true;
  for (int i = 2;i <= sq; ++i) {
     if (p[i]) {
        primes.push_back(i);
        int j = 2 * i;
        while (j <= sq) {
          p[j] = false;
          j += i;
        }
     }
  }
  delete p;
}

int main() {
  init();
  int pc = primes.size();
  int n;
  while (cin >> n) {
   int first = true;
    if (n == 0) 
      break;
    cout << n << " = ";
    if (n == 1) {
      cout << 1 << endl;
      continue;
    }
    if (n < 0) {
      cout << "-1";
      n = -n;
      first = false;
    }
    int i = 0;
    while (i < pc && n != 1) {
      if (n % primes[i] == 0) {
        n /= primes[i];
        if (first)
          first = false; 
        else 
          cout << " x ";
        cout << primes[i];
      } else {
        i++;
      }
    }
    if (n != 1) {
      if (!first)
        cout << " x ";
      cout << n;
    }
    cout << endl;
  }

  return 0;
}
