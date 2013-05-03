#include <iostream>
#include <vector>
using namespace std;

void Tab(int tab) {
  for (int i = 0; i < tab; ++i)
    cout << " ";
}

void OutputWriteLine(vector<char>& vec, int tab) {
  Tab(tab);
  cout << "writeln(" << vec[0];
  for (int i = 1; i < vec.size(); ++i)
    cout << "," << vec[i];
  cout << ")" << endl;
}

void OutputIfElseIfElse(int i, int max_i, char smaller, char bigger, int tab) {
  Tab(tab);
  if (i == 0)
    cout << "else" << endl;
  else {
      if (i != max_i)
        cout << "else ";
      cout << "if " << smaller << " < " << bigger << " then" << endl;
  }
}

// remains: [f, e, d] 
// sorted: [small ---> BIG]
void Rec(vector<char>& remains, vector<char>& sorted, int tab) {
  if (remains.size() == 0) {
    OutputWriteLine(sorted, tab);
    return;
  }
  char rem = remains[remains.size() - 1];
  remains.pop_back();
  
  int s_size = sorted.size();
  for (int i = s_size; i >= 0; --i) {
    OutputIfElseIfElse(i, s_size, sorted[i - 1], rem, tab);
    sorted.insert(sorted.begin() + i, rem);
    Rec(remains, sorted, tab + 2);
    sorted.erase(sorted.begin() + i);
  }
  remains.push_back(rem);
}


void Solve(int n) {
  vector<char> sorted;
  sorted.push_back('a');

  vector<char> remains;
  for (int i = n - 1; i > 0; --i)
    remains.push_back((char)'a' + i);
  cout << "program sort(input,output);" << endl;
  cout << "var" << endl;
  cout << "a";
  for (int i = 1; i < n; ++i) 
    cout << "," << (char) ('a' + i);
  cout << " : integer;" << endl;
  cout << "begin" << endl;
  cout << "  readln(a";
  for (int i = 1; i < n; ++i)
    cout << "," << (char) ('a' + i);
  cout << ");" << endl;
  
  Rec(remains, sorted, 2);
  cout << "end." << endl;
}

int main() {
  int m, n;
  cin >> m;
  bool first = true;
  
  while (m-- > 0) {
    if (first)
      first = false;
    else 
      cout << endl;
    cin >> n;
    Solve(n);
  }
}
