#include <iostream>
using namespace std;
string keyboard = 
  "1234567890-=qwertyuiop[]asdfghjkl;\'zxcvbnm,./";

char decode(char c) {
  if (c == ' ')
    return c;

  if ('A' <= c && c <= 'Z')
    c = c - 'A' + 'a';
  
  for (int i = 0; i < keyboard.length(); ++i) {
    if (keyboard[i] == c && i > 1)
      return keyboard[i - 2];
  }
  return c;
}


int main () {
  string line;
  while (getline(cin , line)) {
    int len = line.length();
    for (int i = 0; i < len; ++i) {
      cout << decode(line[i]);
    }
    cout << endl;
  }
  
  
  return 0;
}
