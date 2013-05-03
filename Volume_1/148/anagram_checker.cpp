#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

#define HIST_DEC 0
#define HIST_NEW 1
#define HIST_ADD 2

void Hist(const string& word, int cnt[26]) {
  for (int i = 0; i < 26; ++i)
    cnt[i] = 0;

  for (int i = 0; i < word.length(); ++i) {
    if ('A' <= word[i] && word[i] <= 'Z')
      cnt[word[i] - 'A']++;
  }
}

set<string> dict;
map<string, vector<int> > cnts;

bool ValidWord(int required[26], string word) {
  for (int i = 0; i < 26; ++i) {
    if (required[i] < cnts[word][i]) 
      return false;
  }
  return true;
}

bool ValidWords(string phrase, int required[26], int remain[26], vector<string>& valids) {
  set<string> forbids;
  stringstream ss(phrase);
  string forbid;

  for (int i = 0; i < 26; ++i) 
    remain[i] = 0;

  while (ss >> forbid) {
    if (forbids.find(forbid) == forbids.end()) 
      forbids.insert(forbid);
  }
  set<string>::iterator it;
  for (it = dict.begin(); it != dict.end(); ++it) {
    if (forbids.find(*it) == forbids.end() &&
        ValidWord(required, *it)) {
      valids.push_back(*it);
      for (int i = 0; i < 26; ++i)
        remain[i] += cnts[*it][i];
    }
  }

  // Check if required can be satisfied
  for (int i = 0; i < 26; ++i)
    if (remain[i] < required[i])
      return false;

  return true;
}

void DumpWords(const string& phrase, 
               const vector<string>& valids, 
               const vector<int>& used) {
  cout << phrase << " =";
  for (int i = 0; i < used.size(); ++i)
    cout << " " << valids[used[i]];
  cout << endl;
}

void Rec(const string& phrase,
         int required[26], 
         int remain[26], 
         const vector<string>& valids, 
         int index, 
         vector<int> used) {
  // 1. Success?
  bool success = true;
  for (int i = 0; i < 26; ++i) {
    if (required[i] != 0) {
      success = false;
      break;
    }
  }
  if (success) {
    DumpWords(phrase, valids, used);
    return;
  }
  
  vector<int>& cnt = cnts[valids[index]];
  for (int i = 0; i < 26; ++i) 
    remain[i] -= cnt[i];

  // 2. can we use valids[index] ?
  for (int i = 0; i < 26; ++i)
    required[i] -= cnt[i];

  bool can_use = true;
  for (int i = 0; i < 26; ++i) {
    if (required[i] < 0 || required[i] > remain[i]) {
      can_use = false;
      break;
    }
  }

  if (can_use) {
    used.push_back(index);
    Rec(phrase, required, remain, valids, index + 1, used);
    used.pop_back();
  }

  for (int i = 0; i < 26; ++i)
    required[i] += cnt[i];

  // 3. Can we ignore valids[index]?
  bool can_ignore = true;
  for (int i = 0; i < 26; ++i) {
    if (required[i] > remain[i]) {
      can_ignore = false;
      break;
    }
  }
  if (can_ignore) {
    Rec(phrase, required, remain, valids, index + 1, used);
  }
  
  for (int i = 0; i < 26; ++i) 
    remain[i] += cnt[i];
}

int main() {
  string word;

  while (getline(cin, word)) {
    if (word[0] == '#')
      break;
    else if (dict.find(word) == dict.end()) {
      //cout << word << endl;
      dict.insert(word);
      int cnt[26];
      Hist(word, cnt);
      vector<int> v_cnt;
      for (int i = 0; i < 26; ++i) {
       // cout << cnt[i] << endl; // WOW, they are all zero!
        v_cnt.push_back(cnt[i]);
      }
      cnts[word] = v_cnt;
    }
  }
   
  string phrase;
  int required[26];
  int remain[26];
  while (getline(cin, phrase)) {
    if (phrase == "#")
      break;
    // 1. Compute hist
    for (int i = 0; i < 26; ++i) {
      required[i] = 0;
      remain[i] = 0;
    }
    Hist(phrase, required);
    
    // 2. Build valid words
    vector<string> valids;
    if (ValidWords(phrase, required, remain, valids)) {
      // 3. Recursive call
      vector<int> used;
      Rec(phrase, required, remain, valids, 0, used);
    }
  }
  
}
