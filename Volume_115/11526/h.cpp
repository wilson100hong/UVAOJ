#include <iostream>
using namespace std;
typedef long long LL;

LL Solve(LL n) {
  if (n <= 0 ) return 0;
  LL sum = 0;

  // Step 1
  LL denom = 2, rb = n;  // Right bound
  while (1) {
    LL lb = (n + denom - 1)/ denom;
    if (n % denom * lb == 0) {
      lb++;
    }
    LL range = rb - lb + 1;
    sum += range * (denom - 1);
    rb = lb - 1;
    if (range == 1) break;
    denom++;
  }
  
  // Step 2
  while (rb > 0) {
    sum += (n / rb);
    rb--;
  }
  return sum;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    LL n;
    cin >> n;
    cout << Solve(n) << endl;
  }
}
