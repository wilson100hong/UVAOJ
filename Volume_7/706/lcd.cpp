#include <iostream> 
using namespace std;

bool HT[] = {1, 0, 1, 1, 0, 1, 1, 1, 1, 1};
bool HM[] = {0, 0, 1, 1, 1, 1, 1, 0, 1, 1};
bool HB[] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 1};

int VT[] = {3, 1, 1, 1, 3, 2, 2, 1, 3, 3};
int VB[] = {3, 1, 2, 1, 1, 1, 3, 1, 3, 1};
void horizontal(int n, bool y) {
  cout << " ";
  for (int i = 0; i < n; ++i) {
    cout << (y ? "-" : " ");
  }
  cout << " ";
}

void vertical(int n, int dd) {
  cout << (dd >= 2 ? "|" : " ");
  for (int i = 0; i < n; ++i)
    cout << " ";  
  cout << (dd % 2 == 1 ? "|" : " ");
}


int main () {
  int n;
  string line;
  while (cin >> n >> line) {
    if (n == 0 && line == "0")
      break;
    
    // 1st 
    for (int i = 0; i < line.length(); ++i) {
      horizontal(n, HT[line[i] - '0']);
      if (i != line.length() - 1)
        cout << " ";   
    }
    cout << endl;
    // 2nd
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < line.length(); ++i) {
        vertical(n, VT[line[i] - '0']);
        if (i != line.length() - 1)
          cout << " ";   
      }
      cout << endl;
    } 
    // 3rd
    for (int i = 0; i < line.length(); ++i) {
      horizontal(n, HM[line[i] - '0']);
      if (i != line.length() - 1)
        cout << " ";   
    }
    cout << endl;
    // 4th
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < line.length(); ++i) {
        vertical(n, VB[line[i] - '0']);
        if (i != line.length() - 1)
          cout << " ";   
      }
      cout << endl;
    } 
 
    // 5th
    for (int i = 0; i < line.length(); ++i) {
      horizontal(n, HB[line[i] - '0']);
      if (i != line.length() - 1)
        cout << " ";   
    }
    cout << endl;
    cout << endl;
  }
   
  return 0;
}
