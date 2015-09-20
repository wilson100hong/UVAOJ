#include <iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, age, med;
    cin >> N;
    for (int n = 0; n < N; ++n) {
      cin >> age;
      if (n == N / 2) med = age;
    }
    cout << "Case " << tc << ": " << med << endl;
  }
}
