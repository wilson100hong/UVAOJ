#include <iostream>
using namespace std;
#define MAX 10001

int main() {
  int n;
  while (cin >> n) {
    int two = 0, five = 0, ans = 1;
    for (int i = 1; i <= n; ++i) {
       int j = i;
       while (j % 2 == 0) {
         two++;
         j /= 2;
       }
       while (j % 5 == 0) {
         five++;
         j /= 5;
       }
       ans *= j;
       ans %= 10;
    }
    if (two > five) {
      two -= five;
      while (two > 0) {
        ans *= 2;
        ans %= 10;
        two--;
      }
    } else if (two < five) {
      five -= two;
      ans *= 5;
      ans %= 10;
    }
    cout.width(5);
    cout << n << " -> " << ans << endl;
  }
  return 0;
}
