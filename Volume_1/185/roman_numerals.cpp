#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;

map<char, int> Symbols; 

void Init() {
   Symbols['I']= 1;
   Symbols['V']= 5;
   Symbols['X']= 10;
   Symbols['L']= 50;
   Symbols['C']= 100;
   Symbols['D']= 500;
   Symbols['M']= 1000;
}

int R2A(string roman) {
   int i = 0, n = roman.length();
   int sum = 0;
   while (i < n) {
      char c = roman[i];
      if (i < n - 1 && Symbols[c] < Symbols[roman[i + 1]]) {
        sum += (Symbols[roman[i + 1]] - Symbols[c]);
        i += 2;
      } else {
         sum += Symbols [c];
         i++;
      }
   }
   return sum;
}

map<char, int> mapping;
inline void DumpMapping(int cur) {
   cout << endl;
   cout << "CUR:" << cur << endl;
   map<char, int>::iterator it = mapping.begin();
   for (it = mapping.begin(); it != mapping.end(); ++it) 
      cout << "("<< it->first << it->second << "), ";
   cout << endl;
}

inline bool known(char c) {
   return mapping.find(c) != mapping.end();
}

bool occupied[10];

// Note: here the index is reversed
// Eg.    XVIII
//        01234,   n = 5
//  cur   43210
// The char of cur:  r_[n - 1 - cur];
int DFS(string r1, string r2, string r3, int cur, int carry) {
   //DumpMapping(cur);
   int n1 = r1.length(), n2 = r2.length(), n3 = r3.length();
   if (cur == n3) {
     if (carry == 0 && 
       mapping[r1[0]] != 0 && 
       mapping[r2[0]] != 0 && 
       mapping[r3[0]] != 0) {
       return 1;
     } else {
        return 0;
     }  
   }

   // Test validity of current column
   char c1 = (n1 - 1 - cur >= 0 ? r1[n1 - 1 - cur] : ' ');
   char c2 = (n2 - 1 - cur >= 0 ? r2[n2 - 1 - cur] : ' ');
   char c3 = r3[n3 - 1 - cur];
   int total = 0;

   if (!known(c1)) {
      // Ther are one or two variables uncertain
      for (int i = 0; i < 10; ++i) {
         if (!occupied[i]) {
            occupied[i] = true;
            mapping[c1] = i;
            total += DFS(r1, r2, r3, cur, carry);
            if (total >= 2) 
               return 2;
            mapping.erase(c1);
            occupied[i] = false;
         }
      } 
      return total;
   }  else if (!known(c2)) {
      for (int i = 0; i < 10; ++i) {
         if (!occupied[i]) {
            occupied[i] = true;
            mapping[c2] = i;
            total += DFS(r1, r2, r3, cur, carry);
            if (total >= 2)
               return 2;
            mapping.erase(c2);
            occupied[i] = false;
         }
      }
      return total;
   } else { // both c1 & c2 known
      int d1 = mapping[c1];
      int d2 = mapping[c2];
      int sum = d1 + d2 + carry;
      int dd3 = sum % 10;
      if (!known(c3)) {
         if (occupied[dd3])   {// Already occupied. Dead end!
            return 0;
         }
         occupied[dd3] = true;
         mapping[c3] = dd3;
         total = DFS(r1, r2, r3, cur + 1, sum / 10);
         mapping.erase(c3);
         occupied[dd3] = false;
      } else {
         int d3 = mapping[c3];
         if (sum % 10 != d3)  // Not valid, Dead end!  
            return 0;
         total = DFS(r1, r2, r3, cur + 1, sum / 10);
      }
      return total;
   }
}

// 0: impossible
// 1: valid
// 2: ambiguous
int AAA(string r1, string r2, string r3) {
   if (r1.length() > r3.length() || r2.length() > r3.length())
      return 0;
   mapping.clear();
   mapping[' '] = 0;
   for (int i = 0; i < 9; ++i)
      occupied[i] = false;
   return DFS(r1, r2, r3, 0, 0);
}

string STR[] = {"impossible", "valid", "ambiguous"};
int main() {
   Init();
   string line;
   while (getline(cin, line) && line != "#") {
     stringstream ss(line);
     string r1, r2, r3;
     getline(ss, r1, '+');
     getline(ss, r2, '=');
     ss >> r3;
     string correct = R2A(r1) + R2A(r2) == R2A(r3) ? "Correct" : "Incorrect";
     cout << correct << " ";
     cout << STR[AAA(r1, r2, r3)] << endl;
   }
}
