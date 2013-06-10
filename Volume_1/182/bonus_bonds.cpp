#include <iostream>
#include <sstream>
using namespace std;

typedef unsigned int uint;

int c2i(char c) {
   return (int) (c - '0');
}

uint s2i(string s) {
   // "1234" to 1234
   //  0  <- index
   int sum = 0;
   for (int i = 0; i < s.length(); ++i) 
      sum = sum * 10 + c2i(s[i]);
   return sum;
}

void Print(int n) {
   cout.width(11);
   cout << n << endl;
}

void solve(string bond, int index) {
   // 1. reorder bond
   char tmp = bond[2];
   bond[2] = bond[1];
   bond[1] = bond[0];
   bond[0] = tmp;

   // 2. re-map index
   index--;
   if (index <= 2)
      index = (index + 1) % 3;


   
   int region = c2i(bond[0]);
   int comp = c2i(bond[index]);

   // 3. is index on region bit?
   for (int d = 0; d < 10; ++d) {
      if (index == 0) {  // index is at region bit
         int num = s2i(bond.substr(1, 9));
         if (region == d)  {
            if (region == 0)  // d == 0
               Print(num - 1);
            else 
               Print(num);
         }
         else   Print(0);
      } else { 
         int n1 = s2i(bond.substr(1, index - 1));
         if (d < comp) {
            n1++;
            for (int j = index + 1; j < 10; ++j)
               n1 *= 10;
         } else if (d == comp) {
            for (int j = index + 1; j < 10; ++j)
                  n1 = n1 * 10 + c2i(bond[j]);
         } else {  // d > comp
            // d always not zero so dont need to care about
            for (int j = index + 1; j < 10; ++j)
               n1 *= 10; 
         }
         if (d == 0 && region == 0) 
            n1 --;
         Print(n1);
      }
   }
}

int main() {
   string line;
   bool first = true;
   while (getline(cin, line)) {
      stringstream ss(line);
      string bond;
      int index;
      ss >> bond >> index;
      if (bond == "0000000000" && index == 0)
         break;
      if (!first)
         cout << endl;
      else
         first = false;
      solve(bond, index);  
   }
}
