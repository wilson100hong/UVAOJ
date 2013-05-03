#include <iostream>
#include <vector>

using namespace std;

#define MAX_Y 1024
#define MAX_X 9
#define INF 2147483467

int X[MAX_X];
int Y[MAX_Y];

vector<int> stamps;
int best = 0;

void DumpStampsAndAmount() {
  for (int i = 0; i < stamps.size(); ++i) {
    cout.width(3);
    cout << stamps[i];
  }
  cout << " ->";
  cout.width(3);
  cout << best << endl;
}

void Rec(int cur, int h, int k) {
  // 1. Compute r: 1 ~ r is contiguous
  int r = 0;
  while (r + 1 < MAX_Y && Y[r + 1] != INF) 
    r++;
  // 2. Terminate?
  if (cur == k) {
    if (best < r) {
      best = r;
      stamps.clear();
      for (int i = 0; i < k; ++i)
        stamps.push_back(X[i]);
    }
    return;
  }

  // 3. Not terminate, so lets try all possible X[i]
  // a. Create backup
  int* backup_Y = new int[MAX_Y];
  for (int i = 0; i < MAX_Y; ++i)
    backup_Y[i] = Y[i];

  for (int x = X[cur - 1] + 1; x <= r + 1; ++x) {
    X[cur] = x;
    for (int i = 0; i < MAX_Y; ++i) {
      for (int j = 1; j <= h - Y[i]; ++j) {
        Y[i + j * x] = min(Y[i] + j, Y[i + j * x]);
      }
    }
    // 
    
    Rec(cur + 1, h, k);
    // restore Y with backup_y
    for (int i = 0; i < MAX_Y; ++i)
      Y[i] = backup_Y[i];
  }

  delete backup_Y;
}

int main() {
  // H: num of stamps
  // K: kinds of stamps
  int H, K;
  while (cin >> H >> K) {
    if (H == 0 && K == 0)
      break;
    else {
      // Init
      for (int i = 0; i < MAX_X; ++i)
        X[i] = 0;
      for (int i = 0; i < MAX_Y; ++i)
        Y[i] = INF;
      stamps.clear();
      best = 0;
      X[0] = 1;
      for (int i = 0; i <= H; ++i)
        Y[i] = i;
      Rec(1, H, K);
      DumpStampsAndAmount();
    }
  }
}
