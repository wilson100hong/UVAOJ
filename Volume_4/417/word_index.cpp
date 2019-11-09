#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<string> words;

map<string, int> indices;


void rec(const string& word, int n) {
  if (n == 0) {
    words.push_back(word);
    return;
  }

  int c = word.empty() ? -1 : word[word.size()-1] - 'a';
  for (int x=0;x<26;++x) {
    if (x <= c) continue;
    char y = static_cast<char>('a'+x);
    
    rec(word + y, n-1);
  }
}


int main() {
  // Initialization.
  for (int i=1;i<=5;++i) {
    rec("", i);
  }

  for (int i=0;i<words.size();++i) {
    indices[words[i]] = i + 1;
  }

  string input;
  while (cin >> input) {
    if (indices.count(input)) {
      cout << indices[input] << endl;
    } else {
      cout << 0 << endl;
    }
  }
}
