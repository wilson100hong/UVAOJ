#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
using namespace std;
#define MAX_N 200
int R, C;
bool bitmap[MAX_N][MAX_N];

inline bool C2B(char c) {
   return c == '0' ? false : true;
}
inline string B2C(bool b) {
   return b == false ? "0" : "1";
}
inline void I2RC(int i, int& r, int &c) {
   r = i / C;
   c = i % C;
}

void DumpBitmap() {
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c)
         cout << B2C(bitmap[r][c]);
      cout << endl;
   }
}

void Dump(string s, int width) {
   for (int i = 0; i < s.length(); ++i) {
      if (i > 0 && i % width == 0)
         cout << endl;
      cout << s[i];
   }
   cout << endl;
}

// start point at (r, c) and height = h, width = w, string 
string RecDecompose(int r, int c, int h, int w) {
   if (w <= 0 || h <= 0)
      return "";
   bool all_same = true;
   for (int i = r; i < r + h; ++i) {
      for (int j = c; j < c + w; ++j) {
         if (bitmap[i][j] != bitmap[r][c])  {
            all_same = false;
            break;
         }
      }
   } 
   if (all_same)
      return B2C(bitmap[r][c]);
   else {
      int w2 = w / 2;
      int h2 = h / 2;
      int w1 = w - w2;
      int h1 = h - h2;
      return "D"
        + RecDecompose(r,      c,      h1, w1) 
        + RecDecompose(r,      c + w1, h1, w2) 
        + RecDecompose(r + h1, c,      h2, w1)
        + RecDecompose(r + h1, c + w1, h2, w2);
   }
}

void B2D(string bitmap_str) {
   // 1. write bitmap_str to bitmap
   int r, c;
   int n = bitmap_str.length();
   for (int i = 0; i < n; ++i) {
      I2RC(i, r, c);
      bitmap[r][c] =  C2B(bitmap_str[i]);
   }
   // 2. Decompose 
   string ret = RecDecompose(0, 0, R, C);
   Dump(ret, 50);
}

int RecCompose(const string& s, 
  int p, int r, int c, int h, int w) {
   if (p == s.length() || w <= 0 || h <= 0)
      return p; // does not consume

   if (s[p] == '1' || s[p] == '0') {
      bool b = C2B(s[p]);
      //cout << b << ": " << r << "," << c << "  " << h << "," << w << endl;
      for (int i = r; i <= r + h; ++i)
         for (int j = c; j <= c + w; ++j)
            bitmap[i][j] = b;
     return p + 1;
   } else if (s[p] == 'D')  {
      int w2 = w / 2;
      int h2 = h / 2;
      int w1 = w - w2;
      int h1 = h - h2;
      p++;
      p = RecCompose(s, p, r,      c,      h1, w1);
      p = RecCompose(s, p, r,      c + w1, h1, w2); 
      p = RecCompose(s, p, r + h1, c,      h2, w1);
      p = RecCompose(s, p, r + h1, c + w1, h2, w2);
      return p;
   }
   else {
      cout << "YOU DUMB " << endl;
      return 1000000;
   }
}

void D2B(string d_str) {
   // 1. Compose into bitmap 
   RecCompose(d_str, 0, 0, 0, R, C);
   // 2. Dump from bitmap
   stringstream ss;
   for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
         ss << B2C(bitmap[r][c]);
      }
   }
   // TODO
   string ret =  ss.str();
   Dump(ret, 50);
}

bool isFormatLine(string line) {
   return line[0] == '#' || 
     ((line[0] == 'B' || line[0] == 'D') && 
     line[1] == ' ');
}
int main() {
   string line;
   getline(cin, line);
   while (1) {
      if (line == "#")
         break;
      string binary = "";
      stringstream ss(line);
      char format;
      ss >> format >> R >> C;
      while (getline(cin, line)) {
         if (isFormatLine(line)) {
            break;
         } else {
            binary += line;
         }
      }
      if (format == 'B') {
         cout << "D";
         cout.width(4);
         cout << R;
         cout.width(4);
         cout << C << endl;
         B2D(binary);
      } else {// 'D'
         cout << "B";
         cout.width(4);
         cout << R;
         cout.width(4);
         cout << C << endl;
         D2B(binary);
      }
   }
}
