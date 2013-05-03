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

   string _INST1[] = {"_INST", "_NAV"}; // priority
   GRAMMER.push_back(a2v(_INST1, 2));
   string _INST2[] = {"_INST", "_TK"}; // priority
   GRAMMER.push_back(a2v(_INST2, 2));
   string _INST3[] = {"_INST", "_INST", "AND", "_INST"}; // priority
   GRAMMER.push_back(a2v(_INST3, 4));
}

string VALIDS[] = {
  "CHANGE", "AVERAGE", "SPEED", "CAS",
  "RECORD", "TIME", "TO", "KMH",
  "AT", "FIRST", "SECOND", "THIRD",
  "RIGHT", "LEFT", "GO", "KEEP",
  "AND", "THEN"};

bool ParseSimpleTokens(vector<string>& tokens) {
   int index = 0;
   while (index < tokens.size()) {
      bool valid = false;
      string token = tokens[index];
      // 1. make sure all non-nnn, non-sign tokens are legal
      for (int i = 0; i < 18; ++i>) {
         if (VALIDS[i] == token) {
            valid = true;
            break;
         }
      }
      // 2. check all nnn tokens are legal and into _NNN
      if (!valid) {
         bool all_digit = true;
         for (int i = 0; i < token.length(); ++i) {
            all_digit &= isdigit(token[i]);
         }
         valid = all_digit;
      }
      // 3. check all sign tokens are legal and into _SIGN
      if (!valid) {
         if (token[0] == '"') {
            // TODO: keep fetch token until reach tailing '"'
            // NOTE: here all multi-spaces in a sign will be reduce into only 1 space
         }
      }

      if (!valid)
         return false;
      index++;
   }
}

bool Match(const vector<string>& tokens, 
  const int index, 
  const vector<string>& rule) {
   // TODO

}

string Solve(vector<string>& tokens) {
   vector<string> orig_tokens = tokens;
   if (!ParseSimpleTokens(tokens)) 
      return "Trap!";
   for (int i = 0; i < GRAMMER.size(); ++i) {
      int j = 0;
      while (j < tokens.size()) {
         if (Match(tokens, j, GRAMMER[i])) {
            // TODO: use grammer to reduce sentence

            continue; // repeat in the same place again
         }
         j++;
      }
   }
   if (tokens.size() == 1 && tokens[0] == "_INST") {
      // TODO: return with concatenating orig_tokens
   
   } else 
      return "Trap!";
}

int main() {
   InitGrammer();
   // TEST: dump grammer
   for (int i = 0; i < GRAMMER.size(); ++i) {
      for (int j = 0; j < GRAMMER[i].size(); ++j)
         cout << GRAMMER[i][j] << ", ";
      cout << endl;
   }
/*
   string line;
   vector<string> tokens;
   int i = 1;
   while(getline(cin, line) && line != "#") {
      tokens.clear();
      stringstream ss(line);
      string token;
      while (ss >> token) 
         tokens.push_back(token);
      
      cout.width(3);
      cout << i << ". " << Solve(tokens) << endl;
      i++;
   }
   */
}
