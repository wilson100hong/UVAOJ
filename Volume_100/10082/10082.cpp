#include <iostream>
#include <string>
using namespace std;
string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./";

char wertyu(char c) {
  if (c==' ' || c=='`' || c=='Q' || c=='A' || c=='Z') {
    return c;
  } 
  for (int i=0;i<keyboard.length();++i) {
    if (keyboard[i] == c) {
      return keyboard[i-1];
    }
  }
  return c;
}



int main() {
  string line;
  while(getline(cin, line)) {
    for (int i=0;i<line.length();++i){
      cout << wertyu(line[i]);
    }
    cout << endl;
  }
  return 0;
}
