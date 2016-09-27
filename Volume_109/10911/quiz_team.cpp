// 2016/09/27
// STARS: **
// SKILLS: dp, bitmask
// NOTE: ((a & 1) == 0)   instead of (a && 1 == 0)
//
//
// TODO: wrong
#include <iomanip>
#include <iostream>
#include <math.h>
#include <cstdint>
#include <vector>

using namespace std;

struct Person {
  string name;  // TODO: useless
  int x;
  int y;
};

double dist(const vector<Person>& people, int i, int j) {
  const Person& pi = people[i];
  const Person& pj = people[j];
  int dx = pi.x - pj.x;
  int dy = pi.y - pj.y;
  return sqrt(static_cast<double>(dx*dx + dy*dy));
}

double rec(const vector<Person>& people,
    vector<double>& dp, int n, int state) {
  //cout << "state: " << state << endl;
  if (dp[state] != -1.0) {
    //cout << "cache: " << dp[state] << endl;
    return dp[state];
  }
  // i: the first alone person
  int i = 0;
  int clone = state;
  for (;i<n;++i) {
    if ((clone & 1) == 0) {
      clone = clone >> 1;
      break;
    }
    clone = clone >> 1;
  }
  // try all rest alone person j, j > i
  for (int j=i+1;j<n;++j) {
    if ((clone & 1) == 0) {
      int new_state = state | (1<<i) | (1<<j);
      double cost = dist(people, i, j) + rec(people, dp, n, new_state);
      if (dp[state] == -1.0 || cost < dp[state]) {
        dp[state] = cost;
      }
    }
    clone = clone >> 1;
  }
  //cout << "derive: " << dp[state] << endl;
  return dp[state];
}

double solve(const vector<Person>& people) {
  int n = people.size();
  // dp[i]: min sum of distances to pair all people
  // 0: alone 1: paired
  vector<double> dp(1<<n, -1.f);
  dp[(1<<n)-1] = 0.f;
  return rec(people, dp, n, 0);
}

int main() {
  int N, x, y;
  string name;
  int cases = 1;
  while (1) {
    vector<Person> people;
    cin >> N;
    if (N == 0) break;
    for (int i=0;i<2*N;++i) {
      cin >> name >> x >> y;
      people.push_back({name, x, y});
    }
    double ans = solve(people);
    cout << "Case " << cases++ << ": ";
    cout << fixed;
    cout << setprecision(2) << ans << endl;
  }
}
