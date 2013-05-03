#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

enum SYMBOL{
  A = 0, MOD, BA, DA, LA, NAM,
  PREDA, SENT, PCLAIM,
  PREDS, PNAME, PSTR,
  PVERB, STATE, VPRED, 
  EMPTY};

string S_S[] = {
  "A", "MOD", "BA", "DA", "LA", "NAM",
  "PREDA", "SENT", "PCLAIM",
  "PREDS", "PNAME", "PSTR",
  "PVERB", "STATE", "VPRED", 
  "EMPTY"};

// First, Second, Thrid, Result
int RULES[][4] = { 
{PREDA, PREDA, EMPTY, PREDA},
{PREDA, EMPTY, EMPTY, PSTR},
{NAM,   EMPTY, EMPTY, PNAME},
{LA,    PSTR,  EMPTY, PNAME},
{MOD,   PSTR,  EMPTY, VPRED}, // 5
{PSTR,  A,     PSTR,  PSTR},
{PSTR,  EMPTY, EMPTY, PREDS},
{DA,    PREDS, EMPTY, PCLAIM},
{PNAME, BA,    PREDS, PCLAIM},
{PNAME, VPRED, EMPTY, PVERB}, // 10
{PVERB, PNAME, EMPTY, STATE},
{PVERB, EMPTY, EMPTY, STATE},
{PCLAIM,EMPTY, EMPTY, SENT},
{STATE, EMPTY, EMPTY, SENT}
};


#define RN 14

bool isVowel(char c) {
  return c == 'a' || c == 'e' ||  c == 'i' || c == 'o' || c == 'u';
}

bool isCons(char c) {
  return !isVowel(c);
}

int StringToToken(string s) {
  int len = s.length();
  if (isCons(s[len - 1])) {
    return NAM; 
  }
  if (len == 1)
    return A;
  if (len == 5) {
    // CCVCV CVCCV
    bool is_preda = isVowel(s[4]) && isCons(s[3]) && isCons(s[0]);
    is_preda = is_preda && 
        ( (isCons(s[1]) && isVowel(s[2]))  ||  
          (isVowel(s[1]) && isCons(s[2])) );
    return is_preda ? PREDA : EMPTY;
  }
  if (s[0] == 'g')
    return MOD;
  if (s[0] == 'b')
    return BA;
  if (s[0] == 'd')
    return DA;
  if (s[0] == 'l')
    return LA;
  cout << "WTF" << endl;
  return -1;
}

int main() {
  string line;
  vector<int> tokens;
  bool last_line = false;
  vector<int>::iterator it;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    stringstream ss(line);
    string token;
    while (ss >> token) {
      if (token[token.length() - 1] == '.') {
        token = token.substr(0, token.length() - 1);
        last_line = true;
      }
      tokens.push_back(StringToToken(token));
    }
    
    if (last_line) {
      // Loop all rules 
      for (int i = 0; i < RN; ++i) {
        it = tokens.begin();
        while (it != tokens.end()) {
          vector<int>::iterator end = tokens.end();
          // First not equal
          if (RULES[i][0] != *it) {
            it++;
            continue; 
          }
          // Second not equal 
          if (RULES[i][1] != EMPTY && 
              (it == end - 1 || RULES[i][1] != *(it + 1))) {
            it++;
            continue;
          }
          // Third not equal
          if (RULES[i][2] != EMPTY &&
              (it == end - 2 || RULES[i][2] != *(it + 2))) {
            it++;
            continue;
          }
          // Delete and replace
          if (RULES[i][2] != EMPTY)
            tokens.erase(it + 2);
          if (RULES[i][1] != EMPTY)
            tokens.erase(it + 1);
          *it = RULES[i][3];
        }   
      }
      if (tokens.size() == 1 && tokens[0] == SENT) 
        cout << "Good" << endl;
      else 
        cout << "Bad!" << endl;
      tokens.clear();
      last_line = false;
    }
  }
}
