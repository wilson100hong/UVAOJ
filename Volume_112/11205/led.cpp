#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef unsigned int UI;

// number of zero
int noz(UI x, int P) { 
  int cnt = 0;
  for (int i = 0; i < P; ++i) {
    cnt += !(x & 1);
    x = x>>1;
  }
  return cnt;
}

void dump_mask(UI x, int P) {
  for (int i = 0; i < P; ++i) {
    cout << ((x & 1) ? "1" : "0" );
    x = x>>1;
  }
  cout << endl;
}

bool has_dup(const vector<UI> numbers, UI mask, int P) {
  set<UI> r;
  for (const UI& n : numbers) {
    UI n_n = n & mask;
    if (r.count(n_n)) {
      return true;
    }
    r.insert(n_n);
  }
  return false;
}


int main() {
  int TC;
  cin >> TC;
  while (TC-- > 0) {
    int P, N;
    cin >> P >> N;
    vector<UI> numbers;
    for (int n = 0; n < N; ++n) {
      UI x = 0;
      char c;
      for (int p = 0; p < P; ++p) {
        cin >> c;
        if (c == '1') {
          x += (1 << p);
        }
      }
      numbers.push_back(x);
    }

    int best = 0;
    for (UI mask = (1 << P) - 1; mask > 0; --mask) {
      int nz = noz(mask, P);
      if (nz > best && !has_dup(numbers, mask, P)) {
        best = nz;
      }
    }
    cout << P - best << endl;
  }
}
