// 2016/09/25
// STARS: **
// SKILLS: dp, bitmask
// trap: memset(_, _, num) num is # of bytes! be sure to use sizeof() !
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

#define N 12
int DP[1<<N];

typedef uint16_t State;

// DEBUG usage
string dump(State state) {
  string res;
  for (int i=0;i<N;++i) {
    char c;
    if (state & 1) {
      c = 'o';
    } else {
      c = '-';
    }
    res = c + res;
    state = state >> 1;
  }
  return res;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int rec(State state) {
  if (DP[state] != -1) {
    return DP[state];
  }
  State clone = state;
  int cnt = 0;
  for (int i=0;i<N; ++i) {
    if (clone & 1) {
      cnt++;
    }
    clone = clone >> 1;
  }
  DP[state] = cnt;

  clone = state;
  for (int i=0; i<N-2;++i) {
    uint16_t rest = clone & 7;
    if (rest == 3 || rest == 6) {
      uint16_t mask = ~(7<<i);
      State nstate = state & mask;
      if (rest == 3) {
        // -oo -> o-- : 3 -> 4
        nstate |= (4<<i);
      } else if (rest == 6) {
        // oo- -> --o: 6 -> 1
        nstate |= (1<<i);
      }
      DP[state] = min(DP[state], rec(nstate));
    }
    clone = clone >>1;
  }
  return DP[state];
}

int solve(const string& str) {
  // convert str to int number
  // index
  // str index: 0123456789ab
  //            ---oo-------
  // uint_16t:  0000 0001 1000 0000
  State state = 0;
  for (int i=0;i<str.size();++i) {
    if (i>0) {
      state = state<<1;
    }
    if (str[i] == 'o') {
      state |= 1;
    }
  }
  return rec(state); 
}

int main() {
  string line;
  memset(DP, -1, sizeof(int)*(1<<N));
  for (int i=0;i<(1<<N);++i) {
    if (DP[i]!=-1) {
      cout << "DP["<<i<<"] != -1" << endl;
    }
  }
  int n;
  cin >> n;
  getline(cin, line);
  while (n--) {
    getline(cin, line);
    cout << solve(line) << endl;
  }
}
