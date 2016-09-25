// Trap: give up sequence when sum < 0, not sum <= 0
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string solve(const vector<int>& road, int route) {
  int n = road.size();
  // find max sum sequence
  int cur_nice = 0;
  int cur_len = 0;
  int cur_begin = -1;

  int best_nice = 0;
  int best_len = 0;
  int best_begin = -1;

  for (int i=0;i<n;++i) {
    if (cur_nice + road[i] < 0) {
      // reset
      cur_len = 0;
      cur_nice = 0;
    } else {  // cur_nice + road[i] > 0, can keep continue
      if (cur_len == 0) {
        cur_begin = i;
      }
      cur_nice += road[i];
      cur_len++;

      if ((cur_nice > best_nice) ||
          (cur_nice == best_nice && cur_len > best_len)) {
        best_nice = cur_nice;
        best_len = cur_len;
        best_begin = cur_begin;
      }
    }
  }

  if (best_nice == 0) {
    return "Route " + to_string(route) + " has no nice parts";
  } else {
    return "The nicest part of route " + to_string(route) + " is between stops "
      + to_string(best_begin+1) +" and " + to_string(best_begin+best_len+1);

  }
}

int main() {
  int cases;
  cin >> cases;
  for (int route=1;route<=cases;++route) {
    int S;
    cin >> S;
    vector<int> road(S-1, 0);
    for (int i=0;i<S-1;++i) {
      cin >> road[i];
    }
    cout << solve(road, route) << endl;
  }
}
