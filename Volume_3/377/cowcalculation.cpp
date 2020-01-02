#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <sstream>
using namespace std;

string Padding(const string& s) {
  string res(s);
  while (res.size() < 8) {
    res = "V" + res;
  }
  return res;
}

map<char, int> C2I = {
  {'V', 0},
  {'U', 1},
  {'C', 2},
  {'D', 3}
};

char I2C[] = {'V', 'U', 'C', 'D'};

pair<char, char> Add(char c1, char c2, char carry) {
  int sum = C2I[c1] + C2I[c2] + C2I[carry];
  return {I2C[sum / 4], I2C[sum % 4]};
}

string Add(const string& n1, const string& n2) {
  int z1 = n1.size(), z2 = n2.size();
  string res(max(z1, z2) + 1, 'V');
  char carry = 'V';
  for (int i=n1.size()-1,j=n2.size()-1,k=res.size()-1; k>=0; i--,j--,k--) {
    char c1 = i >= 0 ? n1[i] : 'V';
    char c2 = j >= 0 ? n2[j] : 'V';
    pair<char, char> pp = Add(c1, c2, carry);
    res[k] = pp.second;
    carry = pp.first;
  }
  return res;
}

string Calc(const string& n1, const string& n2, const string& op) {
  string res;
  if (op == "N") {
    res = n2;
  } else if (op == "R") {
    res = "V" + n2.substr(0, n2.size() - 1);
  } else if (op == "L") {
    res = n2 + "V";
  } else if (op == "A") {
    res = Add(n1, n2);
  }
  return res;
}

stringstream SS;
int main() {
  string line;
  getline(cin, line);
  SS.str(line);
  int N;
  SS >> N;
  cout << "COWCULATIONS OUTPUT" << endl;
  while (N--) {
    string num1, num2, output;
    getline(cin, num1);
    getline(cin, num2);
    for (int i=0;i<3;++i) {
      string op;
      getline(cin, op);
      num2 = Calc(num1, num2, op);
    }

    getline(cin, output);
    string ans = Padding(num2);
    if (output == ans) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  cout << "END OF OUTPUT" << endl;
}
