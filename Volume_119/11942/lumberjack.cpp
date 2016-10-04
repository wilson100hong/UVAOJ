#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

bool inc(const vector<int>& jacks) {
  for (int i=1;i<jacks.size();++i) {
    if (jacks[i] < jacks[i-1]) return false;
  }
  return true;
}

bool dec(const vector<int>& jacks) {
  for (int i=1;i<jacks.size();++i) {
    if (jacks[i] > jacks[i-1]) return false;
  }
  return true;
}

int main() {
  int N;
  eatline() >> N;
  cout << "Lumberjacks:" << endl;
  while (N--) {
    stringstream& ss = eatline();
    int beard;
    vector<int> jacks;
    while (ss >> beard) {
      jacks.push_back(beard);
    }
    if (inc(jacks) || dec(jacks)) {
      cout << "Ordered" << endl;
    } else {
      cout << "Unordered" << endl;
    }
  }
}
