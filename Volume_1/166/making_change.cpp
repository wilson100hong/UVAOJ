#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

// NOTE: here we normalize all coins
//  5c -> 1
// 10c -> 2
// 20c -> 4
// 50c -> 10
// $1  -> 20
// $2  -> 40

#define TREASURE_MAX 40
#define TREASURE_TYPE 6
#define TRAN_MAX 100
#define PAID_MAX TREASURE_MAX + TRAN_MAX

int treasure[TREASURE_TYPE] = {1,2,4,10,20,40};
int shopper_cnt[TREASURE_MAX];

void BuildShopper() {
  for (int i=0;i<TREASURE_MAX;++i) {
    shopper_cnt[i] = i;
    for (int j=0;j<TREASURE_TYPE;++j) {
      if (i >= treasure[j] && shopper_cnt[i - treasure[j]] + 1 < shopper_cnt[i] )
        shopper_cnt[i] = shopper_cnt[i - treasure[j]] + 1; 
    }
    //cout << "i: " << i << ", cnt: " << shopper_cnt[i] << endl;
  }
}

int wallet[TREASURE_TYPE];
int dp[PAID_MAX];
int tmp_dp[PAID_MAX];

#define BIG 1<<10

void BuildWallet(int transact) {
  // Init wallet_cnt
  int transact_max = transact + TREASURE_MAX;
  for (int i=0;i<transact_max; ++i)
    dp[i] = -1;   // no way to achieve
  dp[0] = 0;

  int afford = 0; 
  for (int i=0; i<TREASURE_TYPE; ++i) {
    afford += wallet[i] * treasure[i];
    int bound = min(transact_max, afford + 1);
    for (int j=treasure[i]; j< bound; ++j) {
      tmp_dp[j] = dp[j];
      int num = BIG;
      for (int k=1;k<=wallet[i] && j - k*treasure[i] >= 0;++k) {
        if (dp[j - k*treasure[i]] >= 0) 
          num = min(num, dp[j - k*treasure[i]] + k);
      }
      //cout << "J:" << j << " NUM:" << num << endl;
      if (num < BIG) {
        if (dp[j] == -1 || num < dp[j])  {
          tmp_dp[j] = num; 
        }
      }
    }
    // copy tmp_dp to dp
    for (int j=treasure[i]; j< bound; ++j) 
      dp[j] = tmp_dp[j];
    /*
    cout << "I = " << i << endl;
    for (int i=0;i<transact + TREASURE_MAX; ++i)
    cout << "paid: " << i << ", cnt: " <<  dp[i] << endl;
 */ 
  }
  
  // TEST
}

int MinTransaction(int transact) {
  int best = 1 << 10;
  int best_i;
  for (int i=transact; i<transact + TREASURE_MAX; ++i) {
    if (dp[i] > 0) {
      int num = dp[i] + shopper_cnt[i-transact];
      if (num < best) {
        best = num;
        best_i = i;
      }
    }
  }
  //cout << "best I:" << best_i << endl;
  return best;
}

int main() {
  BuildShopper();
  while (1) {
    bool not_all_zero = false;
    for (int i=0;i<TREASURE_TYPE;++i) {
      cin >> wallet[i];
      not_all_zero = not_all_zero || (wallet[i] != 0);
    }
    if (not_all_zero) {
      double money;
      cin >> money;
      int transact = money * 20;
      BuildWallet(transact);
      int best;
      best = MinTransaction(transact);
      cout.width(3);
      cout << best << endl;   
    } else {
      break;
    }
  }
}
