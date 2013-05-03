#include <iostream>
using namespace std;

int collatz(int n, int max) {
  int turn = 1;
  while (n != 1 && n <= max) {
    if (n % 2 == 0) {
      n = n / 2;
    }
    else {  
      if (n > 715827822 || (3 *n + 1) > max)  
        return turn;
      n = 3* n + 1;
    }
    turn++;
  }
  return turn;
}


int main () {
  int a, b;
  int round = 1;
  while (cin >> a >> b) {
    if (a == -1 && b == -1)
      break;
   cout << "Case " << round << ": A = " << a << ", limit = " << b << ", number of terms = " <<  collatz(a, b) << endl;
   round++;
  }
  return 0;
}
