// 2016/09/25
// STARS  : 
// SKILLS : dp
//
// trap: there are multiple test cases

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Treature {
  int d;
  int v;
};

struct State {
  int v;  // best value can get at this state
  bool take;
};

void solve(int T, int W, const vector<Treature>& treasures) {
  int N = treasures.size();
  vector<vector<State>> dp(N, vector<State>(T+1, {0, false}));
  // init first row
  for (int t=0;t<=T;++t) {
    const Treature& tr = treasures[0];
    int time = 3*W*tr.d;
    if (t >= time) {
      dp[0][t] = {tr.v, true};
    }
  }
  // do dp
  for (int i=1;i<N;++i) {
    const Treature& tr = treasures[i];
    int time = 3*W*tr.d;
    for (int t=0;t<=T;++t) {
      if (t-time >= 0 &&
          dp[i-1][t-time].v + tr.v > dp[i-1][t].v) {
        dp[i][t] = {dp[i-1][t-time].v + tr.v, true};
      } else {
        dp[i][t] = {dp[i-1][t].v, false};
      }
    }
  }
  cout << dp[N-1][T].v << endl;
  vector<int> taken;
  int cost = T;
  for (int i=N-1;i>=0;--i) {
    if (dp[i][cost].take) {
      taken.push_back(i);
      cost -= 3*W*treasures[i].d;
    }
  }
  // rebuild take treasures
  cout << taken.size() << endl;
  for (int i=taken.size()-1;i>=0;--i) {
    const Treature tr = treasures[taken[i]];
    cout << tr.d << " " << tr.v << endl;
  }
}

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

int main() {
  bool first = true;
  while (1) {
    int T, W;
    eatline() >> T >> W;
    int N;
    eatline() >> N;
    vector<Treature> treasures;
    for (int i=0;i<N;++i) {
      int d, v;
      eatline() >> d >> v;
      Treature treasure = {d, v};
      treasures.push_back(treasure);
    }

    if (!first) {
      cout << endl;
    }
    solve(T, W, treasures);
    first = false;
    string dummy;
    if (!getline(cin, dummy)) break;
  }
}
