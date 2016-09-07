#include <iostream>
using namespace std;

int main() {
  while (1) {
    int K;
    cin >> K;
    if (K == 0) break;
    int N, M;
    cin >> N >> M;
    int X, Y;
    for (int k=0; k<K; ++k) {
      cin >> X >> Y;
      if (X == N || Y == M)
        cout << "divisa" << endl;
      else if (X > N) {
        if (Y > M) {
          cout << "NE" << endl;
        } else {
          cout << "SE" << endl;
        }
      } else if (X < N) {
        if (Y > M) {
          cout << "NO" << endl;
        } else {
          cout << "SO" << endl;
        }
      }
    }
  }
}
