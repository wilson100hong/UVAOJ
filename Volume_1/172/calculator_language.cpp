#include <iostream>
#include <stack>
#include <sstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

map<char, int> symbols;
map<char, int> old_symbols;

#define INF 1 <<30 
int SymbolToNum(string symbol) {
   char c = symbol[0];
   if (isupper(c)) {
      if (symbols.find(c) != symbols.end()) {
         return symbols[c];
      } else {
         symbol[c] = 0;
         return 0;// return 0
      }
   } else if (c == '_' || isdigit(c)) {
      int neg = 1, start = 0;
      int sum = 0;
      if (c == '_') {
         neg = -1;   start = 1;
      }
      for (int i = start; i < symbol.length(); ++i) 
         sum = sum * 10 + ((int) symbol[i] - '0');
      return neg * sum;
   } else {
      cout << "Undefined symbol" << symbol << endl;
      return INF;
   }
}

string NumToSymbol(int n) {
   stringstream ss;
   if (n < 0) {
      ss << "_";
      n *= -1;
   }
   ss << n;
   return ss.str();
}

stack<string> syms;
stack<char> ops;

void Calculate() {
   // Do until
   // 1. ops is emtpy
   // 2. ops top is '('. remember to pop it
   while (!ops.empty()) {
      char op = ops.top();  ops.pop();
      // cout << "OP: " << op << endl;
      if (op == '(')
         break;
      // Do real calculation here ^_<
      else {
         string sym2 = syms.top(); syms.pop();
         int num2 = SymbolToNum(sym2);
         string sym1 = syms.top(); syms.pop();

         if (op == '=') {
            // cout << "ASSIGN" << endl;
            char sym = sym1[0]; // sym == sym1
            /*
            if ((symbols.find(sym) != symbols.end() && symbols[sym] != num2) ||
                (symbols.find(sym) == symbols.end() && num2 != 0)){
               delta[sym] = num2;
            }
            */
            
            symbols[sym] = num2;
            syms.push(NumToSymbol(num2));
         } else {
            int num1 = SymbolToNum(sym1);
            int result = 0;
            //cout << "NUM1: " << num1 << ", NUM2: " << num2 << endl;
            if (op == '+') {
               result = num1 + num2;
            } else if (op == '-') {
               result = num1 - num2;
            } else if (op == '*') {
               result = num1 * num2;
            } else if (op == '/') {
               result = num1 / num2;
            }
            syms.push(NumToSymbol(result));
         }
      }
   }
}

int main() {
  string line;
  while (getline(cin, line) && line != "#") {
    // Assert stacks are empty
    if (!syms.empty() || !ops.empty()) {
       cout << syms.size() << endl;
       cout << "YOU DUMB" << endl;
       return -1;
    }
    
    // Parse line
    string symbol = "";
    for (int i = 0; i < line.length(); ++i) {
      char c = line[i];
      if (isdigit(c) || c == '_') {    // 0 - 9
         symbol += c;
      } else if (isupper(c)) { // A - Z
         symbol = c;
      } else {
         if (symbol != "")
            syms.push(symbol);
         if (c == ')') {
            Calculate();  
         } else if (c != ' '){
            ops.push(c);
         }
         symbol = "";
      }
    }
    // the last token should be operand. Push to stack
    if (symbol != "")
       syms.push(symbol);

    Calculate();

    // TODO: 
    bool is_changed = false;
    map<char, int>::iterator it;
    
    int first = true;
    for (it = symbols.begin(); it != symbols.end(); ++it) {
       char key = it->first;
       int val = it->second;
       if ((old_symbols.find(key) == old_symbols.end() && val != 0) ||
         (old_symbols.find(key) != old_symbols.end() && old_symbols[key] != val)) {
          if (first) 
             first = false;
          else 
             cout << ", ";
          cout << key << " = " << val;
         is_changed = true;
       }
    }
    if (!is_changed) 
       cout << "No Change";
    cout << endl;


    // Clear stacks
    while (!syms.empty()) 
       syms.pop();
    while (!ops.empty())
       ops.pop();
    // copy symbols to old_symbols
    old_symbols = symbols;
  } 
}
