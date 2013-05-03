#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;


char toUpperCase(char c) {
  if ('a' <= c && c <= 'z')
    return c - 'a' + 'A';
  else 
    return c;
}

string toUpperCase(string s) {
  string us(s);
  for (int i=0;i<us.length();++i)
    us[i] = toUpperCase(us[i]);
  return us;
}

char toLowerCase(char c) {
  if ('A' <= c && c <= 'Z')
    return c - 'A' + 'a';
  else 
    return c;
}

string toLowerCase(string s) {
  string ls(s);
  for (int i=0;i<ls.length();++i)
    ls[i] = toLowerCase(ls[i]);
  return ls;
}

struct Index {
  string key;
  int ln; // line number
  int wn; // column number
};

// true if i1 < i2
bool index_sort(const Index& i1, const Index& i2) {
  // 1. compare string
  if (i1.key == i2.key) {
    if (i1.ln == i2.ln) 
      return i1.wn <= i2.wn;
    else 
      return i1.ln < i2.ln;
  } else {
    return i1.key < i2.key;
  }
}

int main() {
  set<string> ignores;
  string word;
  while (cin >> word) {
    if (word == "::")
      break;
    if (ignores.find(word) == ignores.end()) 
      ignores.insert(word);
  }
  string text;
  getline(cin, text);
  vector<string> lines;
  vector<Index> indexs;
  int line_num = 0;
  while (getline(cin, text)) {
    text = toLowerCase(text);
    lines.push_back(text);
    stringstream ss(text);
    string token;
    int word_num = 0;
    while (ss >> token) {
      if (ignores.find(token) == ignores.end()) {
        Index index;
        index.key = token;
        index.ln = line_num;
        index.wn = word_num;
        indexs.push_back(index);
      }
      word_num++;
    }
    line_num++;
  }
  
  sort(indexs.begin(), indexs.end(), index_sort);
  
  for (int i=0; i<indexs.size(); ++i) {
    stringstream text_stream(lines[indexs[i].ln]);
    string WORD = toUpperCase(indexs[i].key);
    int word_num = 0;
    string token;
    bool first = true;
    while (text_stream >> token) {
      if (first)
        first = false;
      else 
        cout << " ";
      if (token == indexs[i].key && word_num == indexs[i].wn) 
        cout << toUpperCase(token);
      else 
        cout << token;
      word_num++;
    }
    cout << endl;
  }
}
