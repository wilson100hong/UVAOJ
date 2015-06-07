#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  string line;
  int round;
  getline(cin, line);
  stringstream ss(line);
  ss >> round;
  bool first = true;
  while (round-- > 0) {
    getline(cin, line);  // skip blank line

    // solve
    vector<int> indice;
    getline(cin, line);
    stringstream ss(line);
    int index;
    while (ss >> index) {
      indice.push_back(index);
    }
    vector<int> mapping(indice.size(), -1);
    for (int i = 0; i < indice.size(); ++i) {
      mapping[indice[i] - 1] = i;
    }

    getline(cin, line);
    vector<string> words;
    stringstream ss2(line);
    string wor;
    while (ss2 >> word) {
      words.push_back(word);
    }


    if (!first) 
      cout << endl;
    for (int m : mapping) {
      cout << words[m] << endl;
    }
    first = false;
  }
}
