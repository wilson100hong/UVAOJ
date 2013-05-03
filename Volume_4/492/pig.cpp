#include <iostream>
using namespace std;

bool isVowel(char c) {
  if ('a' <= c && c <= 'z')
    c = (char) (c - 'a' + 'A');
  return c == 'A' || c == 'E' || c == 'I'
      || c == 'O' || c == 'U';
}

bool isConsonant(char c) {
  return !isVowel(c);
}

int main() {
  string line;
  while (getline(cin, line)) {
    int i = 0, len = line.length();
    bool isWord = false;
    int start = -1;
    while (i < len) {
      char c = line[i];
      if (('a' <= c && c <= 'z')
        ||('A' <= c && c <= 'Z')) {
        if (!isWord) { 
          isWord = true;
          start = i;
        }
      } else {
        if (isWord && start < i) {
          char s = line[start]; 
          if (isConsonant(s)) 
              start++;
          // dump string
          while(start < i)
            cout << line[start++];
          if (isConsonant(s))
            cout << s;
          // append
          cout << "ay";
          isWord = false;    
        }
        cout << c;
      }
      i++;
    }
    
    if (isWord && start < len) {
      char s = line[start]; 
      if (isConsonant(s)) 
        start++;
      // dump string
      while(start < len)
        cout << line[start++];
      if (isConsonant(s))
        cout << s;
      // append
      cout << "ay";
      isWord = false;    
    }
    cout << endl;
  }
  return 0;
}
