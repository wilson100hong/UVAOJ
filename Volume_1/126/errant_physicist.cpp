#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct Term{
  int x;  // exp of x
  int y;  // exp of y
};

// x decreasing, y increasing
struct TermComp {
  bool operator() (const Term& lhs, const Term& rhs) const {
    if (lhs.x == rhs.x) 
      return lhs.y < rhs.y;
    else 
      return lhs.x > rhs.x;
  }
};

int abs(int n) {
  return n > 0 ? n : -n;
}

typedef map<Term, int, TermComp> Polynomial;

bool IsDigit(char c) {
  return '0' <= c && c <= '9';
}

int ToDigit(char c) {
  return c - '0';
}

void ParseLine(string line, Polynomial& poly) {
  line = line + "+";  // super trick;
  int index = 0;
  bool neg = false;
  int coeff = 0;
  int x = 0, y = 0;
  bool meet_x = false, meet_y = false;
  int mode = 0;   // 0: coeff   1: x_exp  2:y_exp
  while (index < line.length()) {
    char c = line[index++];
    if (c == '+' || c == '-') {
      coeff = neg ? -1 * coeff : coeff;
      if (coeff != 0) {
        // Insert / update Term
        Term term;
        if (meet_x && x == 0) x = 1;
        if (meet_y && y == 0) y = 1;
        term.x = x; term.y = y;
        if (poly.find(term) != poly.end()) {
          poly[term] = poly[term] + coeff;
        }
        else
          poly[term] = coeff;
      }
      coeff = 0; x = 0; y = 0; mode = 0;
      meet_x = false; meet_y = false;
      neg = (c == '-');     
    } else if (c == 'x') {
      meet_x = true;
      if (coeff == 0)
        coeff = 1;
      mode = 1;
    } else if (c == 'y') {
      meet_y = true;
      if (coeff == 0)
        coeff = 1;
      mode = 2;
    } else if (IsDigit(c)) {
      int digit = ToDigit(c);
      switch (mode) {
        case 0:
        coeff = coeff* 10 + digit;
        break;
        case 1:
        x = x* 10 + digit;
        break;
        case 2:
        y = y* 10 + digit;
        break;
      }
    }
  }
}

void Multiply(
  Polynomial& poly1,
  Polynomial& poly2,
  Polynomial& result) {
  Polynomial::iterator it1;
  Polynomial::iterator it2;
  for (it1 = poly1.begin(); it1 != poly1.end(); ++it1) {
    Term term1 = it1->first;
    int coeff1 = it1->second;
    for (it2 = poly2.begin(); it2 != poly2.end(); ++it2) {
      Term term2 = it2->first;
      int coeff2 = it2->second;
      Term term;
      term.x = term1.x + term2.x;
      term.y = term1.y + term2.y;
      int coeff = coeff1 * coeff2;
      if (result.find(term) != result.end()) 
        result[term] += coeff;
      else
        result[term] = coeff;
    }
  }
}

void Dump(string s, bool b) {
  if (b)
    cout << s;
  else {
    for (int i = 0; i < s.length(); ++i)
      cout << " ";
  }
}

string Int2Str(int n) {
  string s;
  stringstream ss(s);
  ss << n;
  return ss.str();
}

void DumpTerm(const Term& term, int coeff, bool exp, bool first) {
  if (coeff == 0) 
    return;   // Hope I am not that stupid
  if (first) {
    if (coeff < 0)
      Dump("-", !exp);
  } else {
    cout << " ";  // Shared
    if (coeff < 0)
      Dump("- ", !exp);
    else
      Dump("+ ", !exp);
  }
  coeff = abs(coeff);
  if (coeff != 1 || (term.x == 0 && term.y == 0)) 
    Dump(Int2Str(abs(coeff)), !exp);
  
  if (term.x > 0) {
    Dump("x", !exp);
    if (term.x > 1)
      Dump(Int2Str(term.x), exp);
  }
  if (term.y > 0) {
    Dump("y", !exp);
    if (term.y > 1)
      Dump(Int2Str(term.y), exp);
  }
}

void DumpPoly(Polynomial& poly, bool exp) {
  Polynomial::iterator it;
  bool first = true;
  for (it = poly.begin(); it != poly.end(); ++it) {
    DumpTerm(it->first, it->second, exp, first);
    first = false;
  }
  cout << endl;
}

int main () {
  string line;
  Polynomial poly1;
  Polynomial poly2;
  Polynomial result;

  while (getline(cin, line)) {
    if (line == "#")
      break;
    poly1.clear();
    poly2.clear();
    result.clear();

    ParseLine(line, poly1);
    getline(cin, line);
    ParseLine(line, poly2);
    Multiply(poly1, poly2, result);
    DumpPoly(result, true);
    DumpPoly(result, false);
  }
}
