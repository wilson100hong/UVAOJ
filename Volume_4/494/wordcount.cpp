#include <iostream>
#include <string>
using namespace std;
int main() {
  string line;
  while(getline(cin, line)) {
    int count = 0;
    int i = 0;
    bool isWord = false;
    bool isSpace = true;  // Previous char is space
     while (i < line.length()) {
     char c = line[i];
      if (('a' <= c && c <= 'z' )
                 || ('A'<= c && c <= 'Z')) {
        if (isSpace) {
           isWord = true; 
        } 
        isSpace = false;
      }else {
        if (!isSpace && isWord) {
          count++;  
        }
        isSpace = true;
        isWord = false;
      } 
      i++;
    }

    if (!isSpace && isWord) {
      count++;
    } 
    cout << count << endl;
  }
  return 0;
}
