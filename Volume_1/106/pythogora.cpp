#include <iostream>
using namespace std;

bool p[1000001];

int gcd(int m, int n) {
  if (n > m) 
    return gcd(n, m);
  if (n == 0)
    return m;
  return gcd(n, m % n);
}

int main () {
  int n;
  while (cin >> n) {
    for (int i = 1; i <= n; ++i)
      p[i] = false; 

    // i is odd, j is even
    
    int first = 0;
    for (int i = 1; i*i <= n; i+=2) {
      for (int j = 2; i*i + j*j <= n; j+=2) {
        if (gcd(i, j) == 1) {
          int r = max(i, j);
          int s = min(i, j); 
          int x = r*r - s*s;
          int y = 2*r*s;
          int z = r*r + s*s;
          
          int d = n / z;
          for (int k = 1; k <= d; ++k) {
            p[x*k] = true;
            p[y*k] = true;
            p[z*k] = true;
          }
          first++;
        }
      }
    }
   
   
    int second = 0;
    for (int i = 1; i <= n; ++i)
      if (p[i] == false)
        second++; 
    cout << first << " " << second << endl;   
  }
  

}
