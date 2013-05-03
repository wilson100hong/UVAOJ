#include <iostream>
#include <sstream>
using namespace std;

string itoa(unsigned int n) {
  stringstream converter;
  converter << n;
  return converter.str();
}

bool isPalindrome(string s) {
  for (int i = 0, j = s.length() - 1; i < j; i++, j--) {
    if (s[i] != s[j]) {
      return false;  
    }
  }  
  return true;
}

int pow10(int x, int n) {
  while (n-- > 0) {
    x *= 10;  
  }  
  return x;
}

string revAdd(string s) {
  unsigned int sum = 0;
  int carry = 0;
  for (int i=0, j=s.length()-1; i < s.length(); i++,j--) {
    int digit = (int) (s[i] - '0' + s[j] - '0' + carry);
    carry = digit / 10;
    digit = digit % 10;
    sum += pow10(digit, i); 
  }
  sum += pow10(carry, s.length());
  s = itoa(sum); 
  return s;
}

int main(){
  int rounds;
  
  cin >> rounds;
  while (rounds-- > 0) {
    unsigned int input;
    cin >> input;
    string s = itoa(input);
    int iter = 0;
    do 
    {
      s = revAdd(s);
      iter++;
    } while (!isPalindrome(s));
  
    cout << iter << " " << s << endl;
  }
  return 0;
}
