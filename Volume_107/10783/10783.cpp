#include <iostream>
using namespace std;
int main() {
  int rounds;
  cin >> rounds;
  int turn = 0;
  while (turn++ < rounds) {
    int a, b;
    cin >> a >> b;
    int r = 0;
    if ((a % 2 == 0 && b % 2 == 0) ||
        (a % 2 == 1 && b % 2 == 1)) {
    	r = b % 2 == 1 ? b : 0;
        b = b - 1;
    }
    int num = b - a + 1;
    int sum = (a + b) * num / 2;
    
    if (a % 2 == 0) {
      sum = (sum + num / 2) / 2;
    } else {
      sum = (sum - num / 2) / 2;
    }
    sum += r;
    cout << "Case " << turn << ": " << sum << endl;
  }

  return 0;
}
