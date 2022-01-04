#include <iostream>
using namespace std;


string detect(const string& s) {
  if (s == "HELLO") return "ENGLISH";
  if (s == "HOLA") return "SPANISH";
  if (s == "BONJOUR") return "FRENCH";
  if (s == "HALLO") return "GERMAN";
  if (s == "CIAO") return "ITALIAN";
  if (s == "ZDRAVSTVUJTE") return "RUSSIAN";
  return "UNKNOWN";
}

int main() {
  string s;
  int t = 1;
  while (cin >> s) {
    if (s == "#") break;
    auto v = detect(s);
    cout << "Case " << t++ << ": " << detect(s) << endl;
  }
}
