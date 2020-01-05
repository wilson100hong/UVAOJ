#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ULL;

ULL DP[13][13] = {0};
ULL FAC[13] = {0};

void Init() {
  FAC[0] = 1;
  for (int i=1;i<13;++i) {
    FAC[i] = FAC[i-1]* i;
  }

  DP[1][1] = 1;
  for (int i=2;i<13;++i) {
    // j == 0
    DP[i][0] = (i-1)*DP[i-1][1];
    // j > 0
    for (int j=1;j<i;++j) {
      DP[i][j] = FAC[j]*(DP[i-j][0] + (i-j)*DP[i-1][j]);
    }
    DP[i][i] = FAC[i];
  }
}

int main() {
  Init();
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n; 
    ULL x = DP[n][0], y = FAC[n];
    if (x == 0) {
      cout << "0" << endl;
    } else if (y == 1) {
      cout << x << endl;
    } else {
      cout << x << "/" << y << endl;
    }
  }
}

