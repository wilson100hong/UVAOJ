#include <iostream>
using namespace std;

int gcd(int a, int b) {
  if (b == 0)
    return a;
  else 
    return gcd(b, a % b);
}


int binomial(int n, int k) {
  if (k > n - k)
    k = n - k;
  // k always < n - k
  int* b = new int[k];
  for (int i = 0; i < k; i++)
    b[i] = n - k + i + 1;

  for (int i = 2; i <= k; i++) {
    int a = i;
    int j = 0;
    while (j < k  && a != 1) {
      if (b[j] != 1) {
        int g = gcd(b[j], a);
        if (g != 1) {
          b[j] /= g;
          a /= g; 
        }
      }
      j++;
    } 
  }
  int mul = 1;
  for (int i = 0; i < k; i++)
    mul *= b[i];
  delete b;
  return mul;
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    if ( n == 0 && k == 0)
      break;
    cout << binomial(n, k) << endl;
  }
  return 0;


}
