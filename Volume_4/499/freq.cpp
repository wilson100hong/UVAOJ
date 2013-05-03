#include <iostream>
using namespace std;
int big[26];
int small[26];

void init() {
  for (int i = 0; i < 26; ++i) {
    big[i] = 0;
    small[i] = 0;
  }
}


int main() {
  string line;
  while(getline(cin, line)) {
    init();
    for (int i = 0; i < line.length(); ++i) {
      char c = line[i];
      if ('A' <= c && c <= 'Z') 
        big[c - 'A']++;
      if ('a' <= c && c <= 'z')
        small[c - 'a']++;
    }

    int max = 0;
    for (int i = 0; i < 26; ++i) {
      if (big[i] > max)
        max = big[i];
      if (small[i] > max)
        max = small[i];
    }

    for (int i = 0; i < 26; ++i) 
      if (big[i] == max)
        cout << (char) ('A' + i);

    for (int i = 0; i < 26; ++i)
      if (small[i] == max)
        cout << (char) ('a' + i);

    cout << " " << max << endl;
  } 
}
