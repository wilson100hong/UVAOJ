#include <iostream>
using namespace std;

int main() {
  int cnt[26] = {0};
  bool dumped[26]={false};
  
  int lines;
  cin >> lines;
  string line;
  while(getline(cin, line)) {
    for (int i=0;i<line.length();++i) {
      char c = line[i];
      if ('a' <= c && c <= 'z') {
         c = c - 'a' + 'A';
      }
      if ('A' <= c && c <= 'Z') {
        int index = c - 'A';
        cnt[index]++;
      }
    }
  }

  while(1) {
    int max = 0;
    int letter = -1;
    for (int i=0;i<26;++i) {
      if (!dumped[i] && cnt[i] > max) {
         letter = i;
         max = cnt[i];
      }
    } 
    if (letter != -1) {
      dumped[letter] = true;
      char c = 'A' + letter;
      cout << c << " " << max << endl;
    } else {
      break;  
    }
  }
}
