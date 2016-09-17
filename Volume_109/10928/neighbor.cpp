#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

int main() {
  int cases;
  eatline() >> cases;
  while (cases--) {
    int P;
    eatline() >> P;
    vector<int> cnts;
    for(int p=0; p<P; ++p) {
      eatline();
      int neighbor;
      int ns = 0;
      while (SS >> neighbor) {
        ns++;
      }
      cnts.push_back(ns);
    }

    int min = 100000;
    for (int p=0; p<P; ++p) {
      if (cnts[p] < min) {
        min = cnts[p];
      }
    }
    bool first = true;
    for (int p=0; p<P; ++p) {
      if (cnts[p] == min) {
        if (!first) cout << " ";
        first = false;
        cout << p+1;
      }
    }
    cout << endl;
    eatline();
  }
}

