// 1. update prime to "sqrt" of testing number
// 2. 0 -> 0! WTF
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

typedef long long int LL;

vector<LL> REV;
vector<LL> PRIME;
LL LAST;

LL MAX = 10000001;

void update_prime_to_sqrt(LL limit) {
  while (LAST*LAST <= limit) {
    bool is_prime = true;
    for (LL prime : PRIME) {
      if (prime * prime > LAST) break;
      if (LAST % prime == 0) 
        is_prime = false;
    }
    if (is_prime)
      PRIME.push_back(LAST);
    LAST++;
  }
}

LL factorize(LL n) {
  update_prime_to_sqrt(n);
  LL ret = 0;

  for (LL prime : PRIME) {
    if (prime * prime > n) break;
    while (n % prime == 0) {
      n /= prime;
      ret++;
    }
  }
  if (n == 1)
    return ret;
  else
    return ret+1;
}

void preprocess() {
  LAST = 2;
  REV.push_back(-1); // 0!, invalid value
  REV.push_back(0);  // 1! 
  int index = 2;
  while (REV.back() <= MAX) {
    LL nf = factorize(index);
    REV.push_back(REV.back() + nf);
    index++;
  }
}

int binary_search(LL target) {
  int sz = REV.size() - 1;
  int left = 1, right = sz -1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (REV[mid] == target) {
      return mid;
    } else if (REV[mid] < target) {
      left = mid + 1;
    } else {
      // REV[mid] > target
      right = mid - 1;
    }
  }
  return -1;
}

string solve(LL n) {
  if (n == 0) return "0!";  // WTF
  int index = binary_search(n);
  if (index < 0) return "Not possible.";

  stringstream ss;
  ss << index << "!";
  return ss.str();
}

int main() {
  preprocess();
  LL n;
  int round = 1;
  while (cin >> n) {
    if (n < 0) break;
    cout << "Case " << round << ": " << solve(n) << endl;
    round++;
  }
}
