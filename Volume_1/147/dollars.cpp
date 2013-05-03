#include <iostream>
using namespace std;

#define MAX 6001
#define NUM_COINS 11
unsigned long long dp[MAX];

int coins[NUM_COINS] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};

int main() {
  dp[0] = 1;
  for (int i = 1; i < MAX; ++i)
    dp[i] = 0;

  for (int j = 0; j < NUM_COINS; j++) {
    for (int i = coins[j]; i < MAX; ++i) {
      dp[i] += dp[i - coins[j]];
    }
  }
  
  int a, b;
  char c;
  while (cin >> a >> c >> b) {
    //cout << a << ", " << b << endl;
    int n = a * 100 + b; 
    n /= 5;
    if (n == 0)
      break;
    cout.width(3);
    cout << a << ".";
    cout.fill('0');
    cout.width(2);
    cout << b;
    cout.fill(' ');
    cout.width(17);
    cout << dp[n] << endl;
  }

  return 0;
}
