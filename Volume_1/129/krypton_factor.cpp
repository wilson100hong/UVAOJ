#include <iostream>
#include <vector>
using namespace std;
 
bool IsEasy(const vector<int>& vec) {
  for (int len = 1; len <= vec.size() / 2; ++len) {
    int second = vec.size() - len;
    int first = second - len;
    bool equal = true;
    for (int i = 0; i < len; ++i) {
      if (vec[first + i] != vec[second + i]) {
        equal = false;
        break;
      }
    }
    if (equal)
      return true;
  }
  return false;
}

bool IsValid(const vector<int>& vec) {
  return !IsEasy(vec);
}

void Rec(int n, int L, vector<int>& vec) {
  if (n == 0) 
    return;
  
  // 1. try append 0 ~ L - 1
  for (int i = 0; i < L; ++i) {
    vec.push_back(i);
    if (IsValid(vec)) {
      Rec(n - 1, L, vec);
      return;
    }
    vec.pop_back();
  }
  
  // 2. trace back
  while (vec.size() > 0) {
    int end = vec.back();
    for (int i = end + 1; i < L; ++i) {
      // TODO: can optimize
      vec.pop_back();
      vec.push_back(i);
      if (IsValid(vec)) {
        Rec(n - 1, L, vec);
        return;
      }
    }
    vec.pop_back();
  }
}

void DumpFormatted(const vector<int>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    if (i == 64)
      cout << endl;
    else if (i != 0 && i % 4 == 0)
      cout << " ";
    cout << (char) (vec[i] + 'A' );
  }
  cout << endl;
}

int main () {
  int n, L;
  while (cin >> n >> L) {
    if (n == 0 && L == 0)
      break;
    vector<int> vec;
    Rec(n, L, vec);
    DumpFormatted(vec);
    cout << vec.size() << endl;
  }
}
