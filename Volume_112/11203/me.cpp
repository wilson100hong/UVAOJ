// x >= 1, y >=1, z = y + x
#include <iostream>
#include <vector>
#include <map>
using namespace std;

bool Solve(const string& line) {
  int cur = 0;
  int x = 0, y = 0, z = 0;
  while (cur < line.size()) {
    if (line[cur] == '?') {
      cur++;
      x++;
    } else if (line[cur] == 'M') {
      cur++;
      break;
    } else {
      //cout << "#1" << endl;
      return false;
    }
  }
  while (cur < line.size()) {
    if (line[cur] == '?') {
      cur++;
      y++;
    } else if (line[cur] == 'E') {
      cur++;
      break;
    } else {
      //cout << "#2" << endl;
      return false;
    }
  }
  while (cur < line.size()) {
    if (line[cur] == '?') {
      cur++;
      z++;
    } else {
      //cout << "#3" << endl;
      return false;
    }
  }
  //cout << "x: " << x << ", y:" << y << ", z:" << z << endl;
  
  if (x < 1 || y < 1 || z != x + y) {
    return false;
  }
  return  true;
}

int main() {
  int N;
  cin >> N;
  string line;
  getline(cin, line);
  while (N--) {
    getline(cin, line);
    bool res = Solve(line);

    cout << (res ? "theorem" : "no-theorem") << endl;
  }
}
