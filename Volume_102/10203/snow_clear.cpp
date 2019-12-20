#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

int main () {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int T;
  ss >> T;
  bool first = true;
  while (T--) {
    getline(cin, line);
    double sum = 0;
    while (getline(cin, line)) {
      if (line.empty()) {
        break;
      }

      stringstream ss2(line);
      double x0, y0, x1, y1;
      ss2 >> x0 >> y0 >> x1 >> y1;
      sum += hypot(x1-x0, y1-y0) / 1e3;
    }

    int mins = round(sum * 6);

    if (!first) cout << endl;
    first = false;
    cout << (mins / 60) << ":" << setfill('0') << setw(2) << (mins % 60) << endl;
  }
}
