#include <iostream>
#include <limits>
#include <sstream>

#define NUM_ALT 10
#define MAX_MILES 100 + 10
#define INF std::numeric_limits<int>::max()

using namespace std;

int dp[NUM_ALT][MAX_MILES];
int wind[NUM_ALT][MAX_MILES];
int delta[3] = {-1, 0, 1};
int fuel[3] = {60, 30, 20};

int min(int a, int b) {
  return a < b ? a : b;
}

using namespace std;
int main() {
  int round;
  cin >> round;
  while (round-- > 0) {
    int miles;
    cin >> miles;
    miles /= 100;
    for (int alt = NUM_ALT - 1; alt >= 0; --alt) {
      for (int i = 0; i < miles; ++i) {
        int w;
        cin >> w;
        wind[alt][i] = w;
        dp[alt][i] = INF;
      }
    } 

    for (int alt = 0; alt < NUM_ALT; ++alt)
      dp[alt][miles] = INF;

    dp[0][0] = 0;

    for (int mile = 1; mile <= miles; mile++) {
      for (int alt = 0; alt < NUM_ALT; ++alt) {
        for (int d = 0; d < 3; ++d) {
          int prev = alt + delta[d];
          if (0 <= prev && prev < NUM_ALT && dp[prev][mile - 1] != INF) {
            dp[alt][mile] = min(dp[prev][mile - 1] + fuel[d] - wind[prev][mile - 1], dp[alt][mile]);
          }
        }
      }
    }
    cout << dp[0][miles] << endl << endl;
  }
}

