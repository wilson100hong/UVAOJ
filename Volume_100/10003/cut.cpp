#include <iostream>
#include <queue>
#define MAX 1 << 31 - 1

using namespace std;
int main() {
  int l, n;
  while (cin >> l) {
    if (l == 0)
      break;
    cin >> n;
 //   cout << n << endl;
    // dp is 2-d array
    int** dp = new int*[n + 1];
    for (int i = 0; i < n + 1; ++i) { 
      dp[i] = new int[n + 1];
      dp[i][i] = 0;
    }
    int* pos = new int[n + 2];
    pos[0] = 0;
    pos[n + 1] = l;
    for (int i = 0; i < n; ++i) {
      cin >> pos[i + 1];
    }
    // test pos & dp
    //for (int i = 0; i < n + 1; ++i) {
   //   cout << dp[i][i] << endl; 
    // }
    // Do dp here
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= n - i; ++j) {
        int min = MAX;
        for (int k = j; k < j + i; ++k) {
          int cost = dp[j][k] + dp[k + 1][i + j];  
          if (cost < min)
            min = cost;
        }
//        cout << " min of " << j << ", " << j + i << " is " << min << endl;
        dp[j][j + i] = pos[j + i + 1] - pos[j] + min;
      }
    }

    cout << "The minimum cutting is " << dp[0][n] << "." <<  endl;
    // delete dp
    for (int i = 0; i < n + 1; ++i)
      delete dp[i];
    delete dp;
    delete pos;
  }
  return 0;
}
