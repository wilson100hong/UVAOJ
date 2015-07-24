#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

#define EPS 1e-6
using namespace std;
int max(int a, int b) {
  return a > b ? a : b;
}

bool equal(pair<double, double>& s1, pair<double, double>& s2) {
  return abs(s1.first - s2.first) < EPS &&
         abs(s1.second - s2.second) < EPS;
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int round;
  ss >> round;
  getline(cin, line);  // first blank line
  bool first = true;

  while (round-- > 0) {
    vector<pair<int, int>> pts;
    while (getline(cin, line) && line != "") {
      stringstream ss2(line);
      int x, y;
      ss2 >> x >> y;
      pts.push_back(make_pair(x, y));
    }

    int ans = 1;
    for (int i = 0; i < pts.size() - 1; ++i) {  // starting point
      int x1 = pts[i].first, y1 = pts[i].second;
      vector<pair<double, double>> lines;
      int vert = 0;
      for (int j = i + 1; j < pts.size(); ++j) {
        int x2 = pts[j].first, y2 = pts[j].second;
        if (x1 == x2) {  // slope = INF
          vert++;
        } else {
          double dx = static_cast<double>(x1 - x2), dy = static_cast<double>(y1 - y2);
          double m = dy / dx;
          lines.push_back(make_pair(m, y1 - m*x1));
        }
      }
      sort(lines.begin(), lines.end());
      
      // scan array 
      pair<double, double> prev = lines[0];
      int cnt = 1;
      for (int j = 1; j < lines.size(); ++j) {
        if (equal(prev, lines[j])) {
          cnt++;
        } else {
          ans = max(ans, cnt);
          cnt = 1;
        }
        prev = lines[j];
      }
      ans = max(max(ans, cnt), vert);
    }

    if (!first) {
      cout << endl;
    }
    cout << ans + 1 << endl;
    first = false;
  }
}
