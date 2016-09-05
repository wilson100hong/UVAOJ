#include <iostream>
using namespace std;

void solve(int H, int U, int D, int F) {
  int tired = F * U;
  // multiply by 100 to avoid floating point
  H *= 100;
  U *= 100;
  D *= 100;

  int h = 0;  // current height
  int successive = 0;
  for (int days=1;;days++) {
    int up = U - (successive) * tired;
    if (up > 0) {
      successive++;
    }
    // It never recover its fatigue...
    /*
    else {
      successive = 0;
    }
    */

    h += up;
    if (h > H) {
      cout << "success on day " << days << endl;
      return;
    }
    
    h -= D; 

    if (h < 0) {
      cout << "failure on day " << days << endl;
      return;
    }
  }
}

int main() {
  int H, U, D, F;
  while (1) {
    cin >> H >> U >> D >> F;
    if (H == 0) 
      break;
    solve(H, U, D, F);
  }
}
