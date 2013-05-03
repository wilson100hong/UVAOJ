#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

#define MAX_CHAR 20
int dp[MAX_CHAR + 1][MAX_CHAR + 1];

#define DIR_LEFTUP 0 
#define DIR_UP 1
#define DIR_LEFT 2
int di[] = {-1, -1,  0};
int dj[] = {-1,  0, -1};
int dir[MAX_CHAR + 1][MAX_CHAR + 1];
int cnt[MAX_CHAR + 1][MAX_CHAR + 1];

int Diff(char s, char d) {
  return s == d ? 0 : 1;
}

string Padding(int num) {
  stringstream ss;
  ss.width(2);
  ss.fill('0');
  ss << num;
  return ss.str(); 
}

int GetCountFromParentDir(int parent_dir) {
  if (parent_dir == DIR_LEFTUP)
    return 0;
  if (parent_dir == DIR_UP) 
    return -1;
  if (parent_dir == DIR_LEFT)
    return 1;
  else 
    return -1900000;
}

string GenInstruction(string src, string dst) {
  int m = src.length();
  int n = dst.length();
  string ret = "E";
  int cur_cnt = 0;
  // Init dp array
  dp[0][0] = 0; dir[0][0] = DIR_LEFTUP; cnt[0][0] = 0;
  for (int i = 1; i <= m; ++i) {
    dp[i][0] = i;
    dir[i][0] = DIR_UP;
    cnt[i][0] = cnt[i - 1][0] + GetCountFromParentDir(dir[i - 1][0]);
  }
  for (int j = 1; j <= n; ++j) {
    dp[0][j] = j;
    dir[0][j] = DIR_LEFT;
    cnt[0][j] = cnt[0][j - 1] + GetCountFromParentDir(dir[0][j - 1]);
  }

  // Calculate dp array
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      // LEFT UP
      int cur_value = Diff(src[i - 1], dst[j - 1]) + dp[i - 1][j - 1];
      int cur_dir = DIR_LEFTUP;
      int cur_cnt = cnt[i - 1][j - 1] + GetCountFromParentDir(dir[i - 1][j - 1]);
      // UP
      if (1 + dp[i - 1][j] < cur_value) {
        cur_value = 1 + dp[i - 1][j];
        cur_dir = DIR_UP; 
        cur_cnt = cnt[i - 1][j] + GetCountFromParentDir(dir[i - 1][j]);
      }
      // LEFT
      if (1 + dp[i][j - 1] < cur_value) {
        cur_value = 1 + dp[i][j - 1];
        cur_dir = DIR_LEFT;
        cur_cnt = cnt[i][j - 1] + GetCountFromParentDir(dir[i][j - 1]);
      }
      dp[i][j] = cur_value;
      dir[i][j] = cur_dir;
      cnt[i][j] = cur_cnt;
    }
  }
 
  string inst;
  // Trace back from dp[m][n]
  while (! (m == 0 && n == 0)) {
    int prev_m = m + di[dir[m][n]];
    int prev_n = n + dj[dir[m][n]];
   if (dp[prev_m][prev_n] != dp[m][n]) {
      if (dir[m][n] == DIR_UP) {
        // delete
        inst = "D";
        inst += src[m - 1] + Padding(m + cnt[m][n]); 
      } else if (dir[m][n] == DIR_LEFT) {
        // insert 
        inst = "I";
        inst += dst[n - 1] + Padding(m + cnt[m][n] + 1);
      } else {    // 2
        // edit
        inst = "C";
        inst += dst[n - 1] + Padding(m + cnt[m][n]);
      }
      ret = inst + ret;
    }
    m = prev_m;
    n = prev_n;
  }
  return ret;
}

int main() {
    string line;
    while (getline(cin, line)) {
      if (line == "#")
        break;
      
      // Tokenize to src and dst
      int index = 0;
      while (line[index] != ' ') 
        index++; 
      string src = line.substr(0, index);
      int tail = line.length() - index - 1;
      string dst = line.substr(index + 1, max(0, tail)); 
      cout << GenInstruction(src, dst) << endl;
    }
}
