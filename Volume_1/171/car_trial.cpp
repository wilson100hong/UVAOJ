#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

inline vector<string> a2v(string a[], int n) {
   vector<string> v;
   for (int i = 0; i < n; ++i)
      v.push_back(a[i]);
   return v;
}
// Grammer
vector<vector<string> > GRAMMER;
void InitGrammer() {
   GRAMMER.clear();
   string _CAS1[] = {"_CAS", "CAS"};
   GRAMMER.push_back(a2v(_CAS1, 2));
   string _CAS2[] = {"_CAS", "CHANGE", "AVERAGE", "SPEED"};
   GRAMMER.push_back(a2v(_CAS2, 4));

   string _TK1[] = {"_TK", "_CAS", "TO", "_NNN", "KMH"};
   GRAMMER.push_back(a2v(_TK1, 5));
   string _TK2[] = {"_TK", "RECORD", "TIME"};
   GRAMMER.push_back(a2v(_TK2, 3));

   string _WHERE[] = {"_WHERE", "AT", "_SIGN"};
   GRAMMER.push_back(a2v(_WHERE, 3));

   string _WHEN1[] = {"_WHEN", "FIRST"};
   GRAMMER.push_back(a2v(_WHEN1, 2));
   string _WHEN2[] = {"_WHEN", "SECOND"};
   GRAMMER.push_back(a2v(_WHEN2, 2));
   string _WHEN3[] = {"_WHEN", "THIRD"};
   GRAMMER.push_back(a2v(_WHEN3, 2));

   string _DIR1[] = {"_DIR", "RIGHT"};
   GRAMMER.push_back(a2v(_DIR1, 2));
   string _DIR2[] = {"_DIR", "LEFT"};
   GRAMMER.push_back(a2v(_DIR2, 2));

   string _HOW0[] = {"_HOW", "KEEP"};
   GRAMMER.push_back(a2v(_HOW0, 2));
   string _HOW1[] = {"_HOW", "GO", "_WHEN"}; // priority
   GRAMMER.push_back(a2v(_HOW1, 3));
   string _HOW2[] = {"_HOW", "GO"};
   GRAMMER.push_back(a2v(_HOW2, 2));

   string _DIRNAL1[] = {"_DIRNAL", "_HOW", "_DIR", "_WHERE"}; // priority
   GRAMMER.push_back(a2v(_DIRNAL1, 4));
   string _DIRNAL2[] = {"_DIRNAL", "_HOW", "_DIR"};
   GRAMMER.push_back(a2v(_DIRNAL2, 3));

   string _NAV1[] = {"_NAV", "_DIRNAL"}; // priority
   GRAMMER.push_back(a2v(_NAV1, 2));
   string _NAV2[] = {"_NAV", "_NAV", "AND", "THEN", "_NAV"}; // priority
   GRAMMER.push_back(a2v(_NAV2, 5));

   string _INST0[] = {"_INST", "_NAV", "AND", "_TK"}; // priority
   GRAMMER.push_back(a2v(_INST0, 4));
   string _INST1[] = {"_INST", "_NAV"}; // priority
   GRAMMER.push_back(a2v(_INST1, 2));
   string _INST2[] = {"_INST", "_TK"}; // priority
   GRAMMER.push_back(a2v(_INST2, 2));
}

string VALIDS[] = {
  "CHANGE", "AVERAGE", "SPEED", "CAS",
  "RECORD", "TIME", "TO", "KMH",
  "AT", "FIRST", "SECOND", "THIRD",
  "RIGHT", "LEFT", "GO", "KEEP",
  "AND", "THEN"};

bool is_all_digit(string s) {
   for (int i = 0; i < s.length(); ++i) 
      if (!isdigit(s[i]))
         return false;
   return true;
}

bool is_sign_body(string s) {
   int len = s.length();
   if (len > 0 && s[0] == '.') return false;
   for (int i = 0; i < len; ++i) {
      if (!isupper(s[i]) && s[i] != '.')
         return false;
   }
   return true;
}
bool is_sign(string s) {
   int len = s.length();
   // BLOG: trick 2: len > 2
   return len > 2 && s[0] == '"' && s[len - 1] == '"' && is_sign_body(s.substr(1, len - 2));
} 
bool is_sign_head(string s) {
   int len = s.length();
   return len > 1 && s[0] == '"' && is_sign_body(s.substr(1, s.length() - 1));
}
bool is_sign_tail(string s) {
   int len = s.length();
   return len > 1 && s[len - 1] == '"' && is_sign_body(s.substr(0, len - 1));
}

bool ParseSimpleTokens(vector<string>& tokens) {
   int index = 0;
   while (index < tokens.size()) {
      bool valid = false;
      string token = tokens[index];
      int next = index + 1;
      // 1. make sure all non-nnn, non-sign tokens are legal
      for (int i = 0; i < 18; ++i) {
         if (VALIDS[i] == token) {
            valid = true;
            break;
         }
      }
      // 2. check if token is number 
      if (!valid && is_all_digit(token)) {
         tokens[index] = "_NNN";
         valid = true;
      }
      // 3. check if token is the whole sign
      if (!valid && is_sign(token)) {
         tokens[index] = "_SIGN";
         valid = true;
      }
      // 4. check if token is the sign head
      if (!valid && is_sign_head(token)) {
         // NOTE: here all multi-spaces in a sign will be reduce into only 1 space
         while (next < tokens.size()) {
            if (is_sign_tail(tokens[next])) {
               valid = true;   
               break;
            } else if (is_sign_body(tokens[next])) {
               next++;
               continue;
            } else {
               break; // valid = false
            }
         }
         if(valid) {
            vector<string>::iterator it = tokens.begin();
            tokens.erase(it + index, it + next + 1);
            tokens.insert(it + index, "_SIGN");
         }
      }
      if (!valid) 
         return false;
      index = next;
   }
   return true;
}

bool Match(const vector<string>& tokens, 
  const int index, 
  const vector<string>& rule) {
   int rule_len = rule.size() - 1;
   if (index + rule_len > tokens.size())
      return false;
   // The first element of rule is the produced result
   for (int i = 0; i < rule_len; ++i) 
      if (rule[i + 1] != tokens[index + i]) 
         return false;
   return true;
}

string Solve(vector<string>& tokens, bool first_space, bool last_space) {
   // Copy original tokens
   vector<string> orig_tokens = tokens;
   if (!ParseSimpleTokens(tokens)) 
      return "Trap!";
 
   for (int i = 0; i < GRAMMER.size(); ++i) {
      int index = 0;
      while (index < tokens.size()) {
         if (Match(tokens, index, GRAMMER[i])) {
          //  cout << "~~MATCH~~" << endl;
            int rule_len = GRAMMER[i].size() - 1;
            // Reduce patterns
            vector<string>::iterator it = tokens.begin();
            tokens.erase(it + index, it + index + rule_len);
           // cout << "~~earse~~" << endl;
            tokens.insert(it + index, GRAMMER[i][0]);
            continue; // repeat in the same place again
         }
         index++;
      }
   }
   
   if (tokens.size() == 1 && tokens[0] == "_INST") {
      string ret = (first_space ? " " : "");
      ret += orig_tokens[0];
      for (int i = 1; i < orig_tokens.size(); ++i) 
        ret = ret + " " + orig_tokens[i];
      if (last_space)
         ret += " ";
      return ret;
   } else 
      return "Trap!";
}

int main() {
   InitGrammer();
   string line;
   vector<string> tokens;
   int i = 1;
   while(getline(cin, line) && line != "#") {
      tokens.clear();
      stringstream ss(line);
      // BLOG: trick 1: first and last space remain
      bool first_space = line.length() > 0 && line[0] == ' ';
      bool last_space = line.length() >0 && line[line.length() - 1] == ' ';
      string token;
      while (ss >> token) 
        tokens.push_back(token);
      string ans = Solve(tokens, first_space, last_space);
      cout.width(3);
      cout << i << ". ";
      cout << ans << endl;
      i++;
   }
}
