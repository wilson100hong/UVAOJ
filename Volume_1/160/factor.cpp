#include <iostream>
using namespace std;

#define MAX_N 101
int prime[MAX_N];
int prime_cnt;
void init() {
  bool p[MAX_N];
  for (int i = 0; i < MAX_N; ++i)
    p[i] = true;
  for (int i = 2; i < MAX_N; ++i) {
    if (p[i]) {
      int j = i * 2;
      while (j < MAX_N) {
        p[j] = false;
        j += i;
      } 
    }
  }
  prime_cnt = 0;
  for (int i = 2; i < MAX_N; ++i) {
    if (p[i]) {
      prime[prime_cnt] = i;
      prime_cnt++;
     }
  }
} 

int main() {
  init();
  int n;
  int answer[MAX_N];
  while (cin >> n) {
    if (n == 0)
      break;
    for (int i = 0; i < MAX_N; ++i)
      answer[i] = 0;

    for (int i = 2; i <= n; ++i) {
      int num = i;
      int p = 0;
      while (num != 1 && p < prime_cnt) {
        if (num % prime[p] == 0) {
          answer[p]++;
          num /= prime[p];
        } else{
          p++;
        }
      }
    }
    // TODO: width
    cout.width(3);
    cout << n << "! =";
    int i = 0;
    while(answer[i] != 0) {
      if (i != 0 && i % 15 == 0) 
        cout << endl << "      ";
      // TODO: width
      cout.width(3);
      cout << answer[i];
      i++;
    }
    cout << endl;
  }
  return 0;
}
