#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 1<<30

#define  Right 0
#define  Up    1
#define  Left  2
#define  Down  3
#define  NUM_DIR 4

// CCW effect on Right, Up, Left, Down
// {d_row, d_col}
int CCW[4][2] ={
 {0,   1}, // Right 
 {-1, -1}, // Up
 {1,  -1}, // Left
 {0,   1}, // Down 
};
int CW[4][2] ={
 {1,   1}, // Right 
 {-1,  1}, // Up
 {0,  -1}, // Left
 {0,  -1}, // Down 
};
struct Point{
  int dir; // false: '_'   true: '|'
  int row;
  int col;
};

// sorting by row: small to bigger
int ComparePoint(const Point& p1, const Point& p2) {
  if (p1.row == p2.row)
    return p1.col < p2.col;
  else
    return p1.row < p2.row;
}

#define UP "v"
#define DOWN "^"
string RecFold(int n, bool up) {
  if (n == 0)
    return "";
  string ditch = (up ? UP: DOWN);
  if (up)
    return RecFold(n - 1, up) + ditch + RecFold(n - 1, !up);
  else // down
    return RecFold(n - 1, !up) + ditch + RecFold(n - 1, up);
}

int Rotate(int dir, char fold) {
  if (fold == 'v') {  // CCW
    return (dir + 1) % NUM_DIR;
  } else { // '^, CW
    return (dir + 3) % NUM_DIR;
  }
}

void DumpCurves(const vector<Point>& curves) {
  for (int i = 0; i < curves.size(); ++i)
    cout << curves[i].dir << "(" << curves[i].row << ", " << curves[i].col << ")" << endl;
  cout << endl;
}

void BuildCurves(string folds, vector<Point>& curves) {
  Point p;
  p.row = 0; p.col = 0;
  p.dir = Right;
  curves.push_back(p);
  for (int i = 0; i < folds.length(); ++i)  {
    // TODO
    // based on folds[i] and p.dir, there will be 
    // different d_row and d_col:
    if (folds[i] == 'v') {
      // CCW
      p.row += CCW[p.dir][0];
      p.col += CCW[p.dir][1];
    } else if (folds[i] == '^') {
      // CW
      p.row += CW[p.dir][0];
      p.col += CW[p.dir][1];
    }
    p.dir = Rotate(p.dir, folds[i]);
    curves.push_back(p);
  }
  //DumpCurves(curves);
}

int MinCol(const vector<Point>& curves) {
  int min =  MAX;
  for (int i = 0; i < curves.size(); ++i)
    if (curves[i].col < min)
      min = curves[i].col;
  return min;
}

void DumpCurves(vector<Point>& curves) {
  sort(curves.begin(), curves.end(), ComparePoint);
  int min_col = MinCol(curves);
  int min_row = curves[0].row;
  int i = 0, col = min_col, row = min_row;
  while (i < curves.size()) {
    int cur_row = curves[i].row;
    int cur_col = curves[i].col;
    while (row < cur_row) {
      cout << endl;
      row++;
      col = min_col;
    }
    while (col < cur_col) {
      // must be in same row
      cout << " ";
      col++;
    } 
    cout << ((curves[i].dir == Up || curves[i].dir == Down )? '|': '_');
    col++;
    i++;
  }
}

void solve(int n) {
  string folds = RecFold(n, true); 
  vector<Point> curves;
  BuildCurves(folds, curves);
  DumpCurves(curves);
  cout << endl << "^" << endl;
}

int main() {
  int n;
  vector<Point> curves;
  while (cin >> n) {
    if (n == 0)
      break;
    solve(n);
    //      string s = RecFold(n, true);
    //      cout << s << endl;
  }
}
