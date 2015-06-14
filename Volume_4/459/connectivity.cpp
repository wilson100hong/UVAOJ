#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

string getline_str() {
  string line;
  if (!getline(cin, line)) {
    return "";
  }
  return line;
}

int getline_int() {
  string line = getline_str();
  stringstream ss(line);
  int n;
  ss >> n;
  return n;
}

vector<int> group;
int num;

// For debug usage
void dump() {
  cout << "index: ";
  for (int i = 0; i < group.size(); ++i) {
    cout << static_cast<char>('A' + i);
  }
  cout << endl << "group: ";
  for (int i = 0; i < group.size(); ++i) {
    cout << static_cast<char>('A' + group[i]);
  }
  cout << endl;
}

void init() {
  num = getline_str()[0] - 'A' + 1;
  group.clear();
  for (int i = 0; i < num; ++i) {
    group.push_back(i);
  }
}

int find(int x) {
  return group[x] == x ? x : (group[x] = find(group[x]));
}

void connect(int x, int y) {
  int gx = find(x), gy = find(y);
  if (gx != gy) {
    group[gx] = gy;
    num--;
  }
}

int main() {
  int round = getline_int();

  string dummy;
  getline(cin, dummy);  // the first blank line

  bool first = true;
  while (round--) {
    init();

    while (1) {
      string str = getline_str();
      if (str == "") {
        if (!first) {
          cout << endl;
        }
        cout << num << endl;
        first = false;
        break;
      }
      int x = str[0] - 'A';
      int y = str[1] - 'A';
      connect(x, y);
    }
  }
}
