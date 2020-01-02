#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

bool IsArabic(const string& s) {
  return '0' <= s[0] && s[0] <= '9';
}

string ToRoman(const string& s) {
  int num = stoi(s); 
  string res = "";

  int thousands = num / 1000;
  num %= 1000;
  while (thousands--) {
    res += "M";
  }
  
  // num < 1000
  int hundreds = num / 100;
  num %= 100;
  if (hundreds == 9) {
    res += "CM";
  } else if (hundreds == 4) {
    res += "CD";
  } else {
    if (hundreds >= 5) {
      res += "D";
      hundreds -= 5;
    }
    while (hundreds--) {
      res += "C";
    }
  }
  // num < 100
  int tens = num / 10;
  num %= 10;
  if (tens == 9) {
    res += "XC";
  } else if (tens == 4) {
    res += "XL";
  } else {
    if (tens >= 5) {
      res += "L";
      tens -= 5;
    }
    while (tens --) {
      res += "X";
    }
  }
  // num < 10
  if (num == 9) {
    res += "IX";
  } else if (num == 4) {
    res += "IV";
  } else {
    if (num >= 5) {
      res += "V";
      num -= 5;
    }
    while (num--) {
      res += "I";
    }
  }

  return res;
}

int ToArabic(const string& s) {
  int i = 0;
  int sum = 0;
  while (i < s.size()) {
    if (s[i] == 'I') {
      if (i < s.size() - 1 && (s[i+1]=='V' || s[i+1]=='X')) {
        if (s[i+1] == 'V') {
          sum += 4;
        } else {  // s[i+1] == 'X'
          sum += 9;
        }
        i+=2;
      } else {
        sum += 1;
        i++;
      }
    } else if (s[i] == 'X') {
      if (i < s.size() - 1 && (s[i+1]=='L' || s[i+1]=='C')) {
        if (s[i+1] == 'L') {
          sum += 40;
        } else {  // s[i+1] == 'C'
          sum += 90;
        }
        i+=2;
      } else {
        sum += 10;
        i++;
      }
    } else if (s[i] == 'C') {
      if (i < s.size() - 1 && (s[i+1]=='D' || s[i+1]=='M')) {
        if (s[i+1] == 'D') {
          sum += 400;
        } else {  // s[i+1] == 'M'
          sum += 900;
        }
        i+=2;
      } else {
        sum += 100;
        i++;
      }
    } else if (s[i] == 'V') {
      sum += 5;
      i++;
    } else if (s[i] == 'L') {
      sum += 50;
      i++;
    } else if (s[i] == 'D') {
      sum += 500;
      i++;
    } else if (s[i] == 'M') {
      sum += 1000;
      i++;
    }
  }
  return sum;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (IsArabic(line)) {
      cout << ToRoman(line) << endl;
    } else {
      cout << ToArabic(line) << endl;
    }
  }
}
