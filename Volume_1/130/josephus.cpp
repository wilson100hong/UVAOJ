#include <iostream>
using namespace std;
#define N_MAX 100
int dp[N_MAX + 1];
int main() {
  int N, K;
  while (cin >> N >> K) {
    if (N == K && K == 0) 
      break;
    dp[1] = 1;
    dp[2] = K % 2 == 0 ? 1 : 2;
    
    for (int i=3; i<=N; ++i) {
      int victim = K % i;
      if (victim == 0)
        victim = i;
      int buryer = victim + K % (i-1);
      if (buryer > i)
        buryer -= i;
      int* mapping = new int[i]; // 1 ~ i-1
      int src_index = victim + 1;
      int dst_index = 1;
      while (dst_index < i) {
        if (src_index > i)
          src_index -= i;
        if (src_index != buryer) {
          if (src_index == victim) {
            mapping[dst_index++] = buryer;
          } else {
            mapping[dst_index++] = src_index;
          }
        }
        src_index++;
      }
      dp[i] = mapping[dp[i-1]];
      delete mapping;
    }
    int diff = dp[N] - 1;   
    int index = 1 - diff;
    if (index <= 0)
      index += N;
    cout << index << endl;
  }
}
