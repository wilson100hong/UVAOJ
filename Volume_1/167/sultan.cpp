#include <iostream>
using namespace std;

#define LEN 8
int occupied[LEN][LEN];
int score[LEN][LEN];

void toggle(int row, int col, int set) {
  for (int i = 1; col + i < LEN; ++i) {
    occupied[row][col + i] +=set;
    int r = row + i;
    if (row + i < LEN)
      occupied[row + i][col + i] += set;
    if (0 <= row - i) 
      occupied[row - i][col + i] += set;
  }
}

void dump() {
 for (int i = 0; i < LEN; ++i) {
   for (int j = 0; j < LEN; ++j) 
     cout << occupied[i][j];
   cout << endl;
 }
 cout << endl;
}

void init() {
  for (int i = 0; i < LEN; ++i)
    for (int j = 0; j < LEN; ++j)
      occupied[i][j] = 0;
}

int recTry(int col, int sum) {
  if (col == LEN)
    return sum;
  int max = 0;
  for (int i = 0; i < LEN; ++i) {
    if (occupied[i][col] == 0) {
      toggle(i, col, 1);
      int tmp = recTry(col+1, sum + score[i][col]);
      if (tmp > max)
        max = tmp;
      toggle(i, col, -1);
    }
  }
  return max;
}

int main() {
  init();
  int k;
  cin >> k;
  while (k-- > 0) {
    for (int i = 0; i < LEN* LEN; ++i) {
      cin >> score[i/LEN][i%LEN];
      occupied[i/LEN][i%LEN] = 0;
    }
    /*
    for (int r = 0; r < LEN; ++r) {
      for (int c = 0; c < LEN; ++c) 
        cout << score[r][c] << " ";
      cout << endl;
    }
    */
    cout.width(5);
    cout << recTry(0, 0) << endl;
  }
}
