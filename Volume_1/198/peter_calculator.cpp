#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <cmath>

#define UNDEF NAN
using namespace std;

void Indent(int tab) {
   while (tab -- > 0)
      cout << " ";
}

string TrimWhiteSpaces(string& line) {
   string s = "";
   for (int i = 0; i < line.length(); ++i) 
      if (line[i] != ' ')
         s += line[i];
   return s;
}

bool HasPrefix(string s, string prefix) {
   int plen = prefix.length();
   return s.length() >= plen && s.substr(0, plen) == prefix;
}

class Factor{
public:
   virtual int Eval() = 0;
   virtual void Dump(int tab) = 0;
};

map<string, int> VAR_VALUES;
map<string, Factor*> VAR_EXPS;
map<string, set<string> > VAR_DEPS; // dependency

bool isVarUndef(string var) {
   return var.length() == 0 || 
     (VAR_EXPS.find(var) == VAR_EXPS.end());
}

class NumFactor: public Factor{
public:
   NumFactor(int n) { num = n;}
   int Eval() {return num;}
   void Dump(int tab) {
      Indent(tab);
      cout << "Num:" << num << endl;
   }
   int num;
};

class VarFactor : public Factor{
public:
   VarFactor(string var_) { var = var_;}
   int Eval() {
      if (isVarUndef(var)) 
         return UNDEF;

      if (VAR_VALUES.find(var) != VAR_VALUES.end()) {
         // in cache VAR_VALUES
         return VAR_VALUES[var];
      } else{
         // NOTE: The VarFactor Eval() should happen in topological order.
         // In this case, there should not be any recursive VarFactor.Eval()
         // in it.
         return VAR_EXPS[var]->Eval();
      }
   }
   void Dump(int tab) {
      Indent(tab);
      cout << "Var:" << var << endl;
   }
   string var;
};

class Expression : public Factor{
public:
   Expression(Factor* first_, vector<char> ops_, vector<Factor*> others_) {
      first = first_;
      ops = ops_;
      others = others_; // TODO: this copy is bad
   }
   int Eval() {
      int ans = first->Eval();
      if (ans == UNDEF)
         return UNDEF;
      for (int i = 0; i < ops.size(); ++i) {
         int other = others[i]->Eval();
         if (other == UNDEF)
            return UNDEF;
         char op = ops[i];
         if (op == '+')
            ans = ans + other;
         else if (op == '-')
            ans = ans - other;
         else if (op == '*')
            ans = ans * other;
         else
            cout << "INVALID OP" << op << endl;
      }
      return ans;
   }
   void Dump(int tab) {
      Indent(tab);
      cout << "Exp:" << endl;
      first->Dump(tab + 2);
      for (int i = 0; i < ops.size(); ++i) {
         Indent(tab + 2);
         cout << ops[i] << endl;
         others[i]->Dump(tab + 2);
      }
   }
   Factor* first;
   vector<char> ops;
   vector<Factor*> others;
}; 

void DumpSet(set<string> ss) {
   for (set<string>::iterator it = ss.begin(); it != ss.end(); it++)
      cout << *it << ",";
}

int ParseNum(string& s, int& cur) {
   int sign = 1;
   if (s[cur] == '-') {
      sign = -1;
      cur++;
   }
   int num = 0;
   while (isdigit(s[cur])) {
      int d = (int) (s[cur] - '0');
      num = num * 10 + d;
      cur++;
   }
   return sign * num;
}

string ParseVar(string& s, int& cur) {
   string var = "";
   if (!isalpha(s[cur])) {
      cout << "ParseVar(): start with non-alpha" << endl;
      return var;
   }
   while (isalpha(s[cur]) || isdigit(s[cur])) {
      var = var + s[cur];
      cur++;
   }
   return var;
}

Factor* ParseExpression(string& s, int& cur, set<string>& deps);

Factor* ParseFactor(string& s, int& cur, set<string>& deps) {
   int len = s.length();
   if (s[cur] == '(') { // TODO: out of boundary?
      cur++;
      Factor* expr = ParseExpression(s, cur, deps);
      if (s[cur] != ')')
         cout << "ParseFactor(): no right parent ')'";
      cur++;   // compensate ')'
      return expr;
   } else if (isdigit(s[cur]) || s[cur] == '-'){
      int num = ParseNum(s, cur);
      return new NumFactor(num);
   } else {
      string var = ParseVar(s, cur);
      deps.insert(var);
      return new VarFactor(var);
   }
}

Factor* ParseTerm(string& s, int& cur, set<string>& deps) {
   int len = s.length();
   Factor* first = ParseFactor(s, cur, deps);
   vector<char> ops;
   vector<Factor*> others;
   while (cur < len && s[cur] == '*') {
      ops.push_back(s[cur++]); 
      Factor* other = ParseFactor(s, cur, deps);
      others.push_back(other);
   }
   return new Expression(first, ops, others);
}

Factor* ParseExpression(string& s, int& cur, set<string>& deps) {
   int len = s.length();
   Factor* first = ParseTerm(s, cur, deps);
   vector<char> ops;
   vector<Factor*> others;
   while (cur < len && (s[cur] == '+' || s[cur] == '-')) {
      ops.push_back(s[cur++]); 
      Factor* other = ParseTerm(s, cur, deps);
      others.push_back(other);
   }
   return new Expression(first, ops, others);
}

void Assign(string& line) {
   string s = TrimWhiteSpaces(line);  // does not hurt
   int cur = 0;
   // get var
   string var = ParseVar(s, cur);
   cur += 2;    // skip ":="
   // get Expression
   set<string> deps;
   Factor* expr = ParseExpression(s, cur, deps);
   VAR_EXPS[var] = expr;
   VAR_DEPS[var] = deps;
}

void BFS(string src, set<string>& visited, set<string>& undefs) {
   visited.clear();
   undefs.clear();

   queue<string> q;
   q.push(src);
   while (!q.empty()) {
      string var = q.front();   q.pop();
      visited.insert(var);
      if (isVarUndef(var)) { // var not defined (not have expression)
         undefs.insert(var);
         // TODO: can exit here
         continue;
      }
      for (set<string>::iterator it = VAR_DEPS[var].begin(); 
        it != VAR_DEPS[var].end(); ++it) {
         string dep = *it;
         if (visited.find(dep) == visited.end()) {
            // Not visit yet
            q.push(dep);
         }
      }
   }
}

bool inVector(vector<string>& vec, string s) {
   for (int i = 0; i < vec.size(); ++i)
      if (vec[i] == s)
         return true;
   return false;
}

// False if acyclic
bool DFS(string var,
  set<string>& visited, 
  vector<string>& sorted) {
   
   if (isVarUndef(var))
      cout << "YOU IDIOT" << endl;

   visited.insert(var);
   for (set<string>::iterator it = VAR_DEPS[var].begin();
        it != VAR_DEPS[var].end();
        ++it) {
      string next = *it;
      if (visited.find(next) == visited.end()) {
         //cout << "traverse" << var << ", " << next << endl;
         if (!DFS(next, visited, sorted))  // has cyclic
            return false;
      } else if (!inVector(sorted, next)){
         // next is visited but not in sorted
         //cout << "Cylic: " << var << ", " << next << endl;
         return false;
      } 
   }
      
   sorted.push_back(var);
   return true;
}

// True if success
bool TopologicalSort(string src, vector<string>& sorted) {
   set<string> deps;
   set<string> undefs;
   BFS(src, deps, undefs);
   if (undefs.size() != 0) {
      //cout << "Undefined: ";  DumpSet(undefs);  cout << endl;
      return false;
   }

   // To here, all var in deps are defined.
   sorted.clear();
   set<string> visited;
   if (!DFS(src, visited, sorted)) {
      //cout << "Cyclic dependency" << endl;
      return false;
   } 
   return true;
}

void Print(string line) {
   string tmp = line.substr(5, line.length() - 5);
   string var = TrimWhiteSpaces(tmp); // does not hurt
   //cout << var << endl;
   vector<string> sorted; // topological sorted
   if(!TopologicalSort(var, sorted)) {
      cout << "UNDEF" << endl;
      return;
   }    
   
   VAR_VALUES.clear();
   // All variables used in this expression are defined and acyclic
   // Calculate all vars in sorted based on topo order.
   for (int i = 0; i < sorted.size(); ++i) {
      string d_var = sorted[i];
      // Save var values to cache
      VAR_VALUES[d_var] = VAR_EXPS[d_var]->Eval();
   }
   cout << VAR_VALUES[var] << endl;
}

void Reset() {
   VAR_EXPS.clear();
   VAR_DEPS.clear();
   VAR_VALUES.clear();
}

int main() {
   string line;
   int n = 1;
   while(getline(cin, line)) {
      line = TrimWhiteSpaces(line);
      //cout << "=================" << endl;
      if (line.find(":=") != string::npos) {
         Assign(line);
      } else if (HasPrefix(line, "PRINT")) {
         //cout << n << ":";
         Print(line);
      } else if (HasPrefix(line, "RESET")) {
         Reset();
      }       
      n++;
   }
}
