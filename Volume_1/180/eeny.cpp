/*
 * This is a typical josephus ring problem. 
 *
 * Trick point: 
 * 1. check lower bound and upper bound in inputs
 * 2. check the safe position feasible. For example,
 *    if there are 61 ppl, safe pos of 36 is not 
 *    achievable -- it won't works because 36 > floor(61 / 2).
 *    That's because safe pos 36 means you must stands
 *    36 ppl away from the start -- impossible for 61 ppl.
 * 3. optmize your code to best 
 */
#include <iostream>
#include <set>
using namespace std;

#define PERIOD 15
#define N 1000001

int dp[N];
void init() {
   dp[0] = -1;
   dp[1] = 0;
   dp[2] = 1;
   for (int i = 3; i <= PERIOD; ++i) 
      dp[i] = (dp[i - 1] + (PERIOD % i)) % i;
   for (int i = PERIOD + 1; i < N; ++i) 
      dp[i] = (dp[i - 1] + PERIOD) % i;
}

int main() {
   init();
   int lb, ub;
   set<int> deads;
   int cnt = 0;
   while (cin >> lb >> ub) {
      if (lb == 0 && ub == 0)
         break;
      if (lb > ub)
         swap(lb, ub);
      
      int limit = lb / 2;
      for (int safe = 1; safe <= limit; ++safe) {
         bool ok = true;
         for (int i = lb; i <= ub; ++i) {
            if (dp[i] == safe || i - dp[i] == safe) {
               ok = false;
               break;
            }
         }
         if (ok) {
            cout << safe << endl;
            break;
         } else if (safe == limit)
            cout << "Better estimate needed" << endl;
      }
   }
}
