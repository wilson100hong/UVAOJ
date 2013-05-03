#include <iostream>
using namespace std;

int ascii(char c) {
  if ('a' <= c && c <= 'z')
    return (int) c - 'a' + 1;
  else if ('A' <= c && c <= 'Z')
    return (int) c - 'A' + 1;
  return 0;
}

int love(string s) {
  int sum = 0;
  int len = s.length();
  for (int i = 0; i < len; ++i) 
    sum += ascii(s[i]);
  
  while (sum >= 10) {
    int ss = sum;
    sum = 0;
    while (ss > 0) {
      sum += (ss % 10);
      ss /= 10;
    }
  }
  return sum;
}

int main() {
  string alice, bob;
  while (getline(cin, alice)) {
    getline(cin, bob);
    int a = love(alice);
    int b = love(bob);
    if (a > b) {
      int tmp = a;
      a = b;
      b = tmp;
    }
    double love_score = (double) a / b;
    love_score *= 100;
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    cout << love_score << " %" <<endl;
  }
}
