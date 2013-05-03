#include <iostream>
using namespace std;
#define N_MAX 7500
long cnt[N_MAX] = {0};
int coin[] = {1, 5, 10, 25, 50};

int main () {
  cnt[0] = 1;

  for (int i = 0; i < 5; ++i) {
    for (int j = coin[i]; j < N_MAX; ++j) 
        cnt[j] += cnt[j - coin[i]];
  }  
  int n;
  while (cin >> n)
    cout << cnt[n] << endl;
  return 0;
}
