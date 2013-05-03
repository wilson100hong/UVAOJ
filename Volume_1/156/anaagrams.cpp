#include <iostream>
#include <vector>
using namespace std;

#define ALPHA_SIZE 26

struct Word{
  string s;
  string letters;
};

int char2IntIgnoreCase(char c) {
  if ('a' <= c && c <= 'z')
    return c - 'a';
  else  // 'A' ~ 'Z'
    return c - 'A';
}

string sortLetters(string s) {
  int cnt[ALPHA_SIZE];
  for (int i = 0; i < ALPHA_SIZE; ++i)
    cnt[i] = 0;
  for (int i = 0; i < s.length(); ++i) 
    cnt[char2IntIgnoreCase(s[i])]++;
  int start = 0;
  for (int i = 0; i < ALPHA_SIZE; ++i) {
    while (cnt[i]-- > 0)
      s[start++] = ((char)i + 'a');
  }
  return s;
}

// <: -1
// ==: 0
// >: 1
int compareInt(int i1, int i2) {
  if (i1 < i2)
    return -1;
  else if (i1 > i2)
    return 1;
  else 
    return 0;
}

int compareChar(char c1, char c2, bool ignoreCase) {
  if (ignoreCase) {
    int i1 = char2IntIgnoreCase(c1);
    int i2 = char2IntIgnoreCase(c2);
    return compareInt(i1, i2);
  } else {
    return compareInt((int)c1, (int)c2);
  }
}

int compareString(string s1, string s2, bool ignoreCase) {
  int i = 0, j = 0;
  int len1 = s1.length(), len2 = s2.length();
  while (i < len1 && j < len2) {
    int c = compareChar(s1[i], s2[j], ignoreCase);
    if (c != 0)
      return c;
    i++; j++;
  }
  return compareInt(len1, len2);
}

int compareWordLetters(const Word& w1, const Word& w2) {
  return compareString(w1.letters, w2.letters, true);
  }

int compareWordString(const Word& w1, const Word& w2) {
  return compareString(w1.s, w2.s, false);
}

int partition(vector<Word>& words, int m, int n,
  int(*compareFunc)(const Word&, const Word&) ) {
  Word pivot = words[n];
  int s = m -1;
  for (int i = m; i < n; ++i) {
    if ( (*compareFunc)(words[i], pivot) < 0) {
      // words[i] < pivot
      s++;
      // swap
      Word tmp = words[s];
      words[s] = words[i];
      words[i] = tmp;
    }
  }
  // swap
  Word tmp = words[n];
  words[n] = words[s+1];
  words[s+1] = tmp;
  return s+1;
}

void qsort(vector<Word>& words, int m, int n, 
  int(*compareFunc)(const Word&, const Word&)) {
  if (m < n) {
    int q = partition(words, m, n, compareFunc);
    qsort(words, m, q-1, compareFunc);
    qsort(words,q+1, n, compareFunc);
  }
}

int main () {
  string s;
  vector<Word> words; 
  while (cin >> s) {
    if (s == "#")
      break;
    Word word;
    word.s = s;
    word.letters = sortLetters(s);
    words.push_back(word);
  }

  qsort(words, 0, words.size() - 1, &compareWordLetters);
  vector<Word> ananagrams;
  int index = 0;
  while (index < words.size()) {
    int next = index + 1;
    while(next < words.size() 
      && 0 == compareWordLetters(words[index], words[next])) {
      next++;
    }
    if (next == index + 1) {
      // is anagram
      ananagrams.push_back(words[index]);
    }
    index = next;
  }
  
  qsort(ananagrams, 0, ananagrams.size() - 1, &compareWordString);
  for (int i = 0; i < ananagrams.size(); ++i)
    cout << ananagrams[i].s << endl;
  
  return 0;
}
