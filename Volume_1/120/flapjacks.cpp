#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void dump(const vector<int>& s) {
  for (int i = 0; i < s.size(); ++i) {
    if (i != 0)
      cout << " ";
    cout << s[i];
  } 
  cout << endl; 
}

int seek(const vector<int>& s, int value) {
  for (int i = 0; i < s.size(); ++i) 
    if (s[i] == value) 
      return i;
  return -1;
}

void swap(vector<int>& s, int i, int j) {
  int tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
}

void flip(vector<int>& s, int index) {
  int i = 0, j = index;
  while (i < j)
    swap(s, i++, j--);
}


int main () {
  string line;
  while(getline(cin, line)) {
    stringstream ss(line);
    vector<int> stack;
    int a;
    while(ss >> a)
      stack.push_back(a);
    dump(stack);
    // deal with max
    int len = stack.size(), i = len - 1;
    while (i > 0) {
      int max = -1;
      int index = -1;
      for (int j = 0; j <= i; ++j) {
        if (stack[j] > max) {
          max = stack[j];
          index = j;
        }
      }
      if (stack[i] != max) {
        if (index != 0) {
          flip(stack, index);
          cout << len - index << " ";
        }
          
        flip(stack, i);
        cout <<  len - i << " ";     
      }
      i--;
    }
    cout << "0" << endl;
  } 
  return 0;
}
