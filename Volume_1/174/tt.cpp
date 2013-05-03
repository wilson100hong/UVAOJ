#include <iostream>
#include <sstream>
using namespace std;
string Trim(string str) {
   stringstream ss;
   for (int i = 0; i < str.length(); ++i)
      if (str[i] != ' ')
         ss << str[i];
   return ss.str();
}

int main() {
   string line;
   getline(cin, line);
   cout << Trim(line) << endl;
}
