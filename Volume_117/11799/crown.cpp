#include <iostream>
#include <sstream>
using namespace std;
int main() {
  int round;
  string line;
  cin >> round;
  getline(cin, line);

  for (int r = 1; r <= round; ++r) {
    getline(cin, line);
    stringstream ss(line);
    int speed, max = -1;
    while (ss >> speed) {
      if (speed > max) max = speed;
    }
    cout << "Case " << r << ": " << max << endl;
  }

}
