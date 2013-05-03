#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// OP
#define AND "AND"
#define OR "OR"
#define NOP "NOP"
// COMMAND
#define TRADE "TRADE"
#define CHEAT "CHEAT"
#define NILL "NULL"

struct Cond {
   bool my;
   int last;
   bool equal; // = or #
   string cmd;
};

Cond* ParseCond(string str, int& pivot) {
   // {MY|YOUR} LAST {1|2} {=|#} {TRADE|CHEAT|NULL}
   Cond* cond = new Cond();
   int len = str.length();
   if (str.substr(pivot, 2) == "MY") {
      cond->my = true;
      pivot += 2;
   } else if (str.substr(pivot, 4) == "YOUR") {
      cond->my = false;
      pivot += 4;
   } else {
      cout << "ParseCond Error: "
           << "Not MY nor YOUR." << endl;
   }
   pivot += 4; // skip "LAST"
   cond->last = (char) (str[pivot++] - '0');
   cond->equal = (str[pivot++] == '=');
   if (str[pivot] == 'T') {
      cond->cmd = TRADE;
      pivot += 5;
   } else if (str[pivot] == 'C') {
      cond->cmd = CHEAT;
      pivot += 5;
   } else if (str[pivot] == 'N') {
      cond->cmd = NILL;
      pivot += 4;
   } else {
      cout << "ParseCond Error: "
           << "Command unknown." << endl;
   }
   return cond;
}

string Cond2Str(Cond* cond) {
   if (cond == NULL)
      return "";
   stringstream ss;
   ss << "{COND: "  
     << " My:" << cond->my
     << " ; Last:" << cond->last
     << " ; Equal:" << cond->equal 
     << " ; Cmd:" << cond->cmd
     << "}";
   return ss.str();
}

struct Condtn {
   string op;
   Cond* cond;
   Condtn* condtn;
};

Condtn* ParseCondtn(string str, int& pivot) {
   int len = str.length();;
   Condtn* condtn = new Condtn();
   condtn->cond = ParseCond(str, pivot);
   if (len - pivot >= 2 && str.substr(pivot, 2) == OR) {
      condtn->op = OR;
      pivot += 2;
      condtn->condtn = ParseCondtn(str, pivot);
   } else if (len - pivot >= 3 && str.substr(pivot, 3) == AND) {
      condtn->op = AND;
      pivot += 3;
      condtn->condtn = ParseCondtn(str, pivot);
   } else {
      condtn->op = NOP;
   }
   return condtn;
}

string Condtn2Str(Condtn* condtn) {
   if (condtn == NULL)
      return "";
   stringstream ss;
   ss << "{CONDTN: "  
     << " Op:" << condtn->op << "; "
     << Cond2Str(condtn->cond) << "; "
     << Condtn2Str(condtn->condtn)
     << "}";
   return ss.str();
}

struct IfStmt;
string IfStmt2Str(IfStmt* ifstmt);
IfStmt* ParseIfStmt(string str, int& pivot);

struct Stmt{
   IfStmt* ifstmt; 
   string cmd;
};

Stmt* ParseStmt(string str, int& pivot) {
   int len = str.length();
   Stmt* stmt = new Stmt();
   stmt->ifstmt = NULL;
   if (len - pivot >= 2 && str.substr(pivot, 2) == "IF") {
      // IfStmt
      stmt->ifstmt = ParseIfStmt(str, pivot); 
   } else if (str[pivot] == 'T') {
      stmt->cmd = TRADE;
      pivot += 5;
   } else if (str[pivot] == 'C') {
      stmt->cmd = CHEAT;
      pivot += 5;
   } else if (str[pivot] == 'N') {
      stmt->cmd = NILL;
      pivot += 4;
   } else {
      cout << "ParseStmt Error: "
           << "Command unknown." << endl;
   }
   return stmt;
}

string Stmt2Str(Stmt* stmt) {
   if (stmt == NULL)
      return "";
   stringstream ss;
   ss << "{STMT: "  
     << IfStmt2Str(stmt->ifstmt) << "; "
     << "Cmd:" << stmt->cmd
     << "}";
   return ss.str();
}

struct IfStmt {
   Condtn* condtn;
   Stmt* then;
   Stmt* els;
};

IfStmt* ParseIfStmt(string str, int& pivot) {
   IfStmt* ifstmt = new IfStmt();
   pivot += 2; // "IF"
   ifstmt->condtn = ParseCondtn(str, pivot);

   if (str.substr(pivot, 4) != "THEN") {
      cout << "ParseIfStmt Error:"
           << "THEN missing." << endl;
   }
   pivot += 4; // "THEN"
   ifstmt->then = ParseStmt(str, pivot);
   if (str.substr(pivot, 4) != "ELSE") {
      cout << "ParseIfStmt Error:"
           << "ELSE missing." << endl;
   }
   pivot += 4; // "ELSE"
   ifstmt->els = ParseStmt(str, pivot);
   return ifstmt;
}

string IfStmt2Str(IfStmt* ifstmt){
   if (ifstmt== NULL)
      return "";
   stringstream ss;
   ss << "{IFSTMT: "  
     << Condtn2Str(ifstmt->condtn)
     << ";" << endl
     << " Then:" << Stmt2Str(ifstmt->then)
     << ";" << endl
     << " Else:" << Stmt2Str(ifstmt->els)
     << "}";
   return ss.str();
}

class Robot{
public:
   Robot(Stmt* program)  {
      prog = program;
      score = 0;
   }

   void Init() {
      for (int i = 0; i < 3; ++i)
         mem[i] = NILL;
   }

   bool EvalCond(Cond* cond, Robot* enemy) {
      if (cond == NULL) 
         return true; // should not happen 
      int last = cond->last;
      string cmd = (cond->my ? mem[last] : enemy->mem[last]);
      return (cond->equal ? cmd == cond->cmd : cmd != cond->cmd);
   }

   bool EvalCondtn(Condtn* condtn, Robot* enemy) {
      if (condtn == NULL)
         return true;
      bool now = EvalCond(condtn->cond, enemy);
      if (condtn->op == "NOP")
         return now; 
      else if (condtn->op == "AND")
         return now && EvalCondtn(condtn->condtn, enemy);
      else if (condtn->op == "OR")
         return now || EvalCondtn(condtn->condtn, enemy);
      else {
         cout << "Error in EvalCondtn: Unknown OP" << endl;
         return "YOU MORON";
      }
   }
   
   string EvalStmt(Stmt* stmt, Robot* enemy) {
      if (stmt == NULL) {
         cout << "Error in EvalStmt: NULL stmt" << endl;
         return "YOU IDIOT";
      }
      if (stmt->ifstmt != NULL) {
        return EvalIfStmt(stmt->ifstmt, enemy);
      } else {
         return stmt->cmd;
      }
   }

   string EvalIfStmt(IfStmt* ifstmt, Robot* enemy) {
      if (ifstmt == NULL) {
         cout << "Error in EvalIfStmt: NULL ifstmt" << endl;
         return "YOU DUMB";
      }
      if (EvalCondtn(ifstmt->condtn, enemy)) {
         return EvalStmt(ifstmt->then, enemy);
      } else {
         return EvalStmt(ifstmt->els, enemy);
      }
   }

   string Action(Robot* enemy)  {
      return EvalStmt(prog, enemy);
   };

   void Memorize(string cmd) {
      mem[2] = mem[1];
      mem[1] = cmd;
   };

   // mem[0]: last 1, mem[1]: last 2
   string mem[3];    
   int score;
   Stmt* prog;
};


void Fight(Robot* r1, Robot* r2, int i1, int i2) {
   r1->Init();
   r2->Init();
   for (int i = 0; i < 10; ++i) {
      string c1 = r1->Action(r2);
      string c2 = r2->Action(r1);
      if (c1 == "TRADE" && c2 == "TRADE") {
         r1->score++;
         r2->score++;
      } else if (c1 == "CHEAT" && c2 == "CHEAT") {
         r1->score--;
         r2->score--;
      } else if (c1 == "CHEAT") {
         r1->score += 2;
         r2->score -= 2;
      } else if (c2 == "CHEAT"){
         r1->score -= 2;
         r2->score += 2;
      } else {
         cout << "WTF" << endl;
      }
      r1->Memorize(c1);
      r2->Memorize(c2);
   }
}

string Trim(string str) {
   stringstream ss;
   for (int i = 0; i < str.length(); ++i)
      if (str[i] != ' ')
         ss << str[i];
   return ss.str();
}

int main() {
   vector<Robot*> robots;
   string str = "", cur = "";
   bool end = false;    // does previous statement end?
   while (getline(cin, cur)) {
      if (end && cur[0] == '#') 
         break;
      int period = cur.find('.');
      if (period == string::npos) {
         str += cur;
         end = true;
      } else {
         // A period is found, parse the str
         str += cur.substr(0, period);
         int pivot = 0;
         // Rmove all whitespace
         str = Trim(str);
         Stmt* prog = ParseStmt(str, pivot);
         // DEBUG
         robots.push_back(new Robot(prog));
         end = true;
         str = "";
      }
   }

   
   // 2. Fight!
   for (int i = 0; i < robots.size(); ++i) {
      for (int j = i + 1; j < robots.size(); ++j) {
         Fight(robots[i], robots[j], i, j);  
      }
      cout.width(3);
      cout << robots[i]->score << endl;
   }
}
