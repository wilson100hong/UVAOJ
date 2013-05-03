#include <iostream>
using namespace std;

char revletter[] = {
  'A', '*', '*', '*', '3',
  '*', '*', 'H', 'I', 'L',
  '*', 'J', 'M', '*', 'O',
  '*', '*', '*', '2', 'T',
  'U', 'V', 'W', 'X', 'Y',
  '5'};

char revnum[] = {
  '1', 'S', 'E', '*', 'Z',
  '*', '*', '8', '*'};

int main() {
  string line;
  while (getline(cin, line)) {
    bool isPalin = true;
    bool isMirror = true;
    int end = line.length() - 1;
    while (line[end] == ' ')
      end--;
    string s = line.substr(0, end + 1);
    
    
    int i = 0, j = s.length() - 1;
    //cout << i << ", " << j << endl;
    while (i <= j) {
      if (isPalin) {
        if (s[i] != s[j]) {
          isPalin = false;
        }
      }
      
      if (isMirror) {
        if ('A' <= s[i] && s[i] <= 'Z') {
          char c = revletter[ s[i] - 'A' ];
          if (c != s[j])
            isMirror = false;
        } else if ('1' <= s[i] && s[j] <= '9') {
          char c = revnum[ s[i] - '1' ] ;
          if (c != s[j])
            isMirror = false;
        }
      }
      if (!isPalin && !isMirror)
        break;
      i++;
      j--;
    }
    cout << s;
    if (isPalin && isMirror)
      cout << " -- is a mirrored palindrome." << endl;
    else if (isPalin) 
      cout << " -- is a regular palindrome." << endl;
    else if (isMirror)
      cout << " -- is a mirrored string." << endl;
    else 
      cout << " -- is not a palindrome." << endl;
    cout << endl;

}
  return 0;
}
