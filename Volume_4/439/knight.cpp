#include <iostream>
#include <queue>

using namespace std;
int chessboard[64];

void clear() {
  for (int i = 0; i < 64; ++i) 
    chessboard[i] = -1;
}

int cell(string s) {
  int c = (int) (s[0] - 'a');
  int r = (int) (s[1] - '1');
  return r * 8 + c; 
}

int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = { 1, -1,  2, -2, 2,-2, 1,-1};

void dump() {
  for (int i = 0; i < 8; ++i){
    for (int j = 0; j < 8; ++j) {
      cout << chessboard[i*8 + j] << ", ";
    }
    cout << endl;
  }
}

int main () {
  string s1, s2;
  while (cin >> s1 >> s2) {
    clear();
    queue<int> q1;
    queue<int> q2;
    int step = 0;
    q1.push(cell(s1));

    while (1) {
      while (!q1.empty()) {
        int knight = q1.front();
        q1.pop();
        if (chessboard[knight] == -1) {
          chessboard[knight] = step;
          int r = knight / 8;
          int c = knight % 8;
          for (int i = 0; i < 8; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (0 <= nr && nr < 8 && 0 <= nc && nc < 8 &&
                chessboard[nr * 8 + nc] == -1) {
              q2.push(nr * 8 + nc);
            }
          }
        }
      }
      if (q2.empty())
        break;
      q1 = q2;
      while(!q2.empty())
        q2.pop();
      // clear q2
      step++; 
    }
    cout << "To get from " << s1 << " to " << s2 << " takes " << chessboard[cell(s2)] << " knight moves." << endl;
  }
  
  return 0;
}
