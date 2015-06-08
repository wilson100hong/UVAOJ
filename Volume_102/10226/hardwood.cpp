#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

void dump(map<string, int>& stats, int sum) {
  for (auto& stat : stats) {
    cout << stat.first << " ";
    double fraction = static_cast<double>(stat.second) * 100 / sum;
    cout << fixed;
    cout << setprecision(4) << fraction << endl;
  }
}

int main() {
  int round;
  cin >> round;
  string line;
  if (round == 0)
    return 0;
  getline(cin, line);  // the line of 'round'
  getline(cin, line);  // first blank line
  bool first = true;
  while (round--) {
    map<string, int> stats;
    int sum = 0;
    while (1) {
      getline(cin, line);
      if (line == "") {
        if (!first) 
          cout << endl;
        dump(stats, sum);
        first = false;
        break;
      }
      sum++;
      if (stats.count(line) == 0) {
        stats[line] = 1;
      } else {
        stats[line]++;
      }
    }
  }
}
