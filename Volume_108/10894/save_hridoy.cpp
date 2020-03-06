#include <iostream>
#include <vector>
using namespace std;

vector<string> SAVE_HRIDOY = {
  "*****..***..*...*.*****...*...*.*****.*****.***...*****.*...*",
  "*.....*...*.*...*.*.......*...*.*...*...*...*..*..*...*..*.*.",
  "*****.*****.*...*.***.....*****.*****...*...*...*.*...*...*..",
  "....*.*...*..*.*..*.......*...*.*.*.....*...*..*..*...*...*..",
  "*****.*...*...*...*****...*...*.*..**.*****.***...*****...*.."
};

vector<string> SAVE_HRIDOY_V;

void Init() {
  vector<int> widths = {5,1,5,1,5,1,5,3,5,1,5,1,5,1,5,1,5,1,5};
  int offset = 0;
  for (int w : widths) {
    if (w == 5) {
      for (int r=0;r<5;++r) {
        SAVE_HRIDOY_V.push_back(SAVE_HRIDOY[r].substr(offset, w));
      }
    } else {
      for (int r=0;r<w;++r) {
        SAVE_HRIDOY_V.push_back(".....");
      }
    }
    offset += w;
  }
}

void PrintStringMultX(const string& s, int x) {
  for (int i=0;i<s.size();++i) {
    for (int j=0;j<x;++j) {
      cout << s[i];
    }
  }
}

void PrintHorizontal(int n) {
  for (int i=0;i<5;++i) {
    for (int j=0;j<n;++j) {
      PrintStringMultX(SAVE_HRIDOY[i], n);
      cout << endl;
    }
  }
  cout << endl << endl;
}

void PrintVerticle(int n) {
  for (int i=0;i<SAVE_HRIDOY_V.size();++i) {
    for (int j=0;j<n;++j) {
      PrintStringMultX(SAVE_HRIDOY_V[i], n);
      cout << endl;
    }
  }
  cout << endl << endl;
}

int main() {
  Init();
  int N;
  while (cin >> N) {
    if (N == 0) break;
    if (N > 0) {
      PrintHorizontal(N);
    } else {  // N < 0
      PrintVerticle(-N);
    }
  }
}
