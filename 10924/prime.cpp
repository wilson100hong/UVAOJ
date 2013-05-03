#include <iostream>
#include <cmath>
using namespace std;
#define N 1050
bool prime[N];

void init() {
  for (int i = 0; i < N; ++i) 
    prime[i] = true;
  int nsq = sqrt(N);
  for (int i = 2; i <= nsq; ++i) {
    if (prime[i]) {
      int j = 2*i;
      while (j < N) {
        prime[j] = false;
        j += i;
      }
    }
  }
}

int cn(char c) {
  if ('a' <= c && c <= 'z') 
    return (int) (c - 'a' + 1);
  if ('A' <= c && c <= 'Z')
    return (int) (c - 'A' + 27);
  return -1;
}

int main () {
  string s;
  init();
  while (cin >> s) {
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
      sum += cn(s[i]);
    }
    if (prime[sum])
      cout << "It is a prime word." << endl;
    else 
      cout << "It is not a prime word." << endl;
  }
  return 0;

}
