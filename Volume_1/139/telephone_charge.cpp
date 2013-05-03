#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
struct Teletype{
   string code;
   string local;
   int type;
   int rate;
};

#define UNDEF 0
#define IDD   1
#define STD   2

bool Match(string number, const Teletype& tt) {
   // 1. see any Teletype can run out of codes
   string code = tt.code;
   if (number.length() < code.length())
      return false;
   for (int i = 0; i < code.length(); ++i) {
      if (number[i] != code[i]) {
         return false;
      }
   }
   // TODO(wilsonhong): not correct
   
   if (tt.type == IDD) {
      int r_len = number.length() - code.length();
      return 4 <= r_len && r_len <= 10;
   } else if (tt.type == STD) {
      int r_len = number.length() - code.length();
      return 4 <= r_len && r_len <= 7;
   } else
      return false;
}

string itoa(int n) {
   stringstream ss;
   ss << n;
   return ss.str();
}

string int2dollar(int n) {
   stringstream ss;
   int dollar = n / 100;
   ss.width(0);
   ss << dollar << ".";
   int cents = n % 100;
   ss.width(2);
   ss.fill('0');
   ss << cents;
   return ss.str();
}

string SPACE = "                          "; // 26 spaces

int main() {
   string line;
   vector<Teletype> types;
   while(getline(cin, line)) {
      if (line == "000000")
         break;
      // 1. Parse line into Teletypes
      Teletype tt;
      stringstream ss(line);
      string code, local;
      int rate;
      getline(ss, code, ' ');
      getline(ss, local, '$');
      ss >> rate;
      tt.code = code;
      tt.type = UNDEF; 
      tt.local = local;
      tt.rate = rate;
      if (code[0] == '0') {
         int len = code.length();
         if (code[1] == '0' && 3 <= len && len <= 5) {
            tt.type = IDD;
            types.push_back(tt);
         } else if (code[1] != '0' && 2 <= len && len <= 6) {
            tt.type = STD;
            types.push_back(tt);
         }
      }
   }

   for (string number; cin >> number && number != "#";) {
      int mins;
      cin >> mins;
      cout << number << SPACE.substr(0, 16 - number.length());

      string strMins = itoa(mins), strRate = "", strPrice = "";
      if (number[0] == '0') {
         string sub = "";
         string local = "Unknown";
         int match = -1;
         for (int i = 0; i < types.size(); ++i) {
            if (Match(number, types[i])) {
               match = i;
               break;
            }
         }
         if (match >= 0) {
            local = types[match].local;
            int t_len = types[match].code.length();
            sub = number.substr(t_len, number.length() - t_len);
            int rate = types[match].rate;
            int price = rate * mins;
            strRate = int2dollar(rate);
            strPrice = int2dollar(price);
         } else {
            strPrice = "-1.00";
         }
         cout << local << SPACE.substr(0, 26 - local.length());
         cout << SPACE.substr(0, 10 - sub.length()) << sub;
      } else {
         // Local
         cout << "Local" << SPACE.substr(0, 21 - 5);
         cout << SPACE.substr(0, 15 - number.length()) << number; 
         strRate = "0.00";
         strPrice = "0.00";
      }
      cout << SPACE.substr(0, 5 - strMins.length()) << strMins;
      cout << SPACE.substr(0, 6 - strRate.length()) << strRate;
      cout << SPACE.substr(0, 7 - strPrice.length()) << strPrice;
      cout << endl;
   }
}
