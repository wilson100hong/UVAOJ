#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int getline_int() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int n;
  ss >> n;
  return n;
}

int main() {
  int round = getline_int();
  while (round-- > 0) {
    map<char, int> price;
    int k = getline_int();
    while (k-- > 0) {
      string line;
      getline(cin, line);
      stringstream ss(line);
      char c;
      int v;
      ss >> c >> v;
      price[c] = v;
    }
    int m = getline_int();
    long long int pay = 0;
    while (m-- > 0) {
      string line;
      getline(cin, line);
      for (char c : line) {
        if (price.count(c) != 0) {
          pay += price[c];
        }
      }
    }
    // formatting
    long long int dollar = pay / 100;
    if (pay == 0) {
      cout << "0.";
    } else {
      cout << dollar << ".";
    }
    int cents = pay % 100;
    if (cents < 10) {
      cout << "0";
    } 
    cout << cents << "$" <<  endl;
  }
}
