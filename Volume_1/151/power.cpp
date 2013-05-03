#include <iostream>
using namespace std;
#define MAX_N 100
#define MAX_M 105
int winner[MAX_N][MAX_M];

void init() {
  for (int j = 1; j < MAX_M; ++j)
    winner[2][j] = 2;
  for (int i = 1; i < MAX_N; ++i)
    winner[i][1] = i;
  
  for (int i = 3; i < MAX_N; ++i) {
    for (int j = 2; j < MAX_M; ++j) {
      int win = winner[i - 1][j];
      win = (win + j - 1) % (i - 1);
      if (win == 0)
        win = i - 1;
      winner[i][j] = win + 1;
    }  
  } 
  
}

void dump() {
  for(int i = 1; i < 20; ++i){
    for (int j =1; j < 22; ++j)
      cout << winner[i][j] << ",";
    cout << endl;
  } 
}

int main() {
  int m, n; 
  init();
  while (cin >> n) {
    if (n == 0) 
      break;
   
    for (m = 1; m < MAX_M; ++m) {
      if (winner[n][m] == 13) {
        cout << m << endl;
        break;
      }
    }
  }
}
