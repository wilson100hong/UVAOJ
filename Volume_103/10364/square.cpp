// I solve this problem by DP with bitmask. Each bitmask denotes a set of
// "used" sticks (1 is used, 0 is not). Bitmask 10011 maps to a subset of
// sticks like {31, 24, 17}. (sticks[0] = 31, sticks[1] = 24, sticks[4] = 17).
//
// For each bitmask B, dp[B] stores the max number of groups the
// bitmask can be divided, where each group has sum equals to square's side
// lenght. Side length is calculated by sitcks_sum / 4. In the essence, dp[B]
// stores the max number of sides that B can formed for square.
//
// For example. sticks_sum = 20, side_length = 5 (20 / 4).
// For a bitmask maps to sticks {2, 3, 4, 5, 6}, we can optimally group sticks into
// 2 groups with sum == 5 ({2,3} and {5}), with 4 and 6 not grouped . We name
// the sum of ungrouped sticks "residue". In this case, the residue is 10 (4 +
// 6).  It can be observed that if residue > side_length, then it is impossible
// to form square for B.
//
// Lets define sub-bitmask. For bitmask B, sub-bitmask B' is a bitmask deduced
// by flipping any bit in B which is 1 to 0. The number of B' sub-bitmasks
// equals to the number of "1"s in B.
//
// Finally, the dp induction:
// dp[B] = max(dp[B'] + 1 : if residue of B = edge / 
//             dp[B']     : if residue of B still < edge,
//             0          : if residue of B > edga,
//             for all B's sub-bitmask B')
//
// natural ordering to scan B is good for us, since we will meet every B' before B.
//
// Most important, we need some optimizations:
// 1. only need to try half of mask -- we can assume stick[m - 1] is always not used.
// 2. dont precompute anything for all bitmask -- no in dp[], no in value[].
// But vector initalization is fine.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

int get_bit(int n, int bit) {
  return (n & (1 << bit)) >> bit;
}

// DEBUG usage
string mask_str(int mask, int m) {
  stringstream ss;
  for (int bit = m - 1; bit >= 0; --bit) {
    ss << get_bit(mask, bit);
  }
  return ss.str();
}

bool solve(vector<int>& sticks) {
  sort(sticks.begin(), sticks.end());
  reverse(sticks.begin(), sticks.end());

  int sum = 0;
  for (int stick : sticks) {
    sum += stick;
  }
  if (sum % 4 != 0) return false;
  int edge = sum / 4;

  for (int stick : sticks) {
    if (stick > edge) 
      return false;
  }

  int m = sticks.size();
  int max = 1 << m;
  vector<int> dp(max, 0);
  vector<int> value(max, 0);
  vector<int> res(max, 0);

  int opt_div = 2;
  for (int mask = 0; mask < max / 2; ++mask) { // Optimization: only need to do half
    for (int bit = 0; bit < m; ++bit) {
      if (get_bit(mask, bit)) {
        value[mask] += sticks[bit];
      }
    }

    for (int bit = 0; bit < m; ++bit) {
      int d = 0;
      int p_mask = mask ^ (1 << bit);  // set mask i-bit to 0
      if (mask & (1 << bit) && res[p_mask] <= edge) {
        int res = value[mask] - dp[p_mask] * edge;
        if (res == edge) {
          d = dp[p_mask] + 1;
        } else if (res < edge) {
          d = dp[p_mask];
        }
      }
      if (d == 3) {
        return true;
      }
      if (dp[mask] < d) {
        dp[mask] = d;
        res[mask] = value[mask] - dp[mask] * edge;
      }
    }
  }
  return false;
}

int main() {
  int T, M, S;
  cin >> T;
  while (T-- > 0) {
    vector<int> sticks;
    cin >> M;
    int sum = 0;
    while (M-- > 0) {
      cin >> S;
      sticks.push_back(S);
    }
    cout << (solve(sticks) ? "yes" : "no" ) << endl;
  }
}
