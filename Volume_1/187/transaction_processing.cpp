#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

void Padding(string s, int width) {
  int len = width - s.length();
  cout << s;
  while (len -- >= 0)
    cout << " ";
}

void DumpAccount(string number, string account, long long amount) {
  cout << number << " ";
  Padding(account, 30);
  cout.fill(' ');

  stringstream ss;
  ss << abs(amount) / 100;
  string aa =  ss.str();
  if (amount < 0)
    aa = "-" + aa;
  cout.fill(' ');
  cout.width(7);
  cout << aa;

  cout << ".";
  cout.fill('0');
  cout.width(2);
  cout << abs(amount) % 100;
  cout << endl;
}

int main() {
  string line;
  map<string, string> accounts;
  while (getline(cin, line)) {
    string number = line.substr(0, 3);
    if (number == "000")
      break;
    accounts[number] = line.substr(3, line.size() - 3);
  }
  // TEST
  long long sum = 0;
  string last_seq = "000";
  map<string, long long> balances;
  vector<string> orders;

  while (getline(cin, line)) {
    string sequence = line.substr(0, 3); 
    if (sequence != last_seq) {
      long long sum = 0;
      map<string, long long>::iterator it;
      for (it = balances.begin(); it != balances.end(); ++it)
        sum += it->second;
      
      if (sum != 0) {
        cout << "*** Transaction " << last_seq << " is out of balance ***" << endl;
        for (int i = 0; i < orders.size(); ++i) 
          DumpAccount(orders[i], accounts[orders[i]], balances[orders[i]]);
        DumpAccount("999", "Out of Balance", -sum);
        cout << endl;
      }
      orders.clear();
      balances.clear();
    }
    if (sequence == "000")
      break;
    else {
      string number = line.substr(3, 3);
      string a_s = line.substr(6, line.length() - 6);
      stringstream ss(a_s);
      long long amount;
      ss >> amount;
      if (balances.find(number) == balances.end()) {
        balances[number] = 0;
        orders.push_back(number);
      }
      balances[number] += amount;
    }
    last_seq = sequence;
  }
}
