// 1. bitwise arithematics in building mask
// 2. recursion
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef unsigned int UI;


void dump_mask(UI x, int P) {
  for (int i = 0; i < P; ++i) {
    cout << ((x & 1) ? "1" : "0" );
    x = x>>1;
  }
  cout << endl;
}

bool duplicate(const vector<UI> numbers, UI mask) {
  set<UI> all;
  for (const UI& n : numbers) {
    UI masked = n & mask;
    if (all.count(masked)) {
      return true;
    }
    all.insert(masked);
  }
  return false;
}

/*
int num_zeros(int P, UI mask) {
    int nz = 0;
    for (int i=0;i<P;++i) {
        if (mask & 1 == 0)
            nz++;
        mask >> 1;
    }
    return nz;
}
*/

int solve(const vector<UI>& numbers, int P, int index, UI mask, int nz) {
    if (index == P) return nz;

    // enable this bit
    UI best = solve(numbers, P, index+1, mask, nz);
    UI mask2 = mask & ( ((1<<P)-1) ^ (1 << index) );
    // cout << "mask2: "; dump_mask(mask2, P);
    if (!duplicate(numbers, mask2)) {
        UI cand = solve(numbers, P, index+1, mask2, nz+1);
        if (cand > best) {
            best = cand;
        }
    }
    return best;
}

int main() {
  int T;
  cin >> T;
  while (T-- > 0) {
    int P, N;
    cin >> P >> N;
    vector<UI> numbers;
    for (int n = 0; n < N; ++n) {
      UI x = 0;
      char c;
      for (int i = 0; i < P; ++i) {
        cin >> c;
        x = x << 1;
        x += (c-'0');
      }
      numbers.push_back(x);
      //dump_mask(x, P);
    }

    cout << P - solve(numbers, P, 0, (1<<P) - 1, 0) << endl;
  }
}
