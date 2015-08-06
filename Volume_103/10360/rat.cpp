#include <iostream>
#define SIZE 1025
using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int main() {
  int city[SIZE* SIZE];
  int round;
  cin >> round;
  while (round-- > 0) {
    int d, n;
    cin >> d >> n;
    // initalize city
    for (int i = 0; i < SIZE* SIZE; ++i) {
      city[i] = 0;
    }

    int best = 0, best_x = -1, best_y = -1;
    for (int i = 0; i < n; ++i) {
      int mx, my, mp;  // p is population
      cin >> mx >> my >> mp;
      for (int y = max(0, my - d); y < min(SIZE, my+d+1); y++) {
        for (int x = max(0, mx - d); x < min(SIZE, mx+d+1); x++) {
          city[y* SIZE + x] += mp;
          if (city[y* SIZE + x] > best) {
            best = city[y* SIZE + x];
            best_x = x; best_y = y;
          }
        }
      } 
    }
    cout << best_x << " " << best_y << " " << best << endl;
  }
}
