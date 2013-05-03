#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Point {
  int x;
  int y;
};

void DumpPoint(Point p) {
  cout << "(" << p.x << "," << p.y << ")";
}

typedef set<Point, bool(*)(const Point&, const Point&)> Board;

void DumpBoard(Board board) {
  Board::iterator it = board.begin();
  while (it != board.end()) {
    DumpPoint(*it);
    cout << ",";
    it++;
  }
  cout << endl;
}


bool ComparePoint(const Point& p1, const Point& p2) {
  if (p1.x == p2.x)
    return p1.y < p2.y;
  else
    return p1.x < p2.x;
}

bool CompareBoard(const Board& b1, const Board& b2) {
  if (b1.size() == b2.size()) {
    Board::iterator it1 = b1.begin();
    Board::iterator it2 = b2.begin();
    while (
      it1 != b1.end() &&
      it2 != b2.end() &&
      it1->x == it2->x && 
      it1->y == it2->y) {
      it1++; it2++; 
    }
    return ComparePoint(*it1, *it2);
  } else {
    return b1.size() < b2.size();
  }
}

void Rotate90(int n, Point& p) {
  int tmp = p.x;
  p.x = p.y;
  p.y = n - tmp - 1; 
}

#define N_MAX 50


void DumpHistory(set< Board, bool(*)(const Board&, const Board&)>& history) {
  set< Board, bool(*)(const Board&, const Board&)>::iterator it = history.begin();
  while (it != history.end()) {
    DumpBoard(*it);
    it++;
  }
  cout << endl;
}

int main() {
  int n;

  Board boards[4] = {
    Board(ComparePoint),
    Board(ComparePoint),
    Board(ComparePoint),
    Board(ComparePoint)
  };
  set< Board, bool(*)(const Board&, const Board&) > history(CompareBoard);

  while (cin >> n) {
    if (n == 0)
      break;
    for (int i = 0; i < 4; ++i)
      boards[i].clear();
    history.clear();

    bool solved = false;
    int x, y;
    char move;
    Point p;
    for (int i = 0; i < 2 * n; ++i) {
      cin >> x >> y >> move;
      x--; y--;
      if (!solved) { 
        p.x = x; p.y = y;
        for (int j = 0; j < 4; ++j) {
          if (move == '+') 
            boards[j].insert(p);         
          else if (move == '-')
            boards[j].erase(p);
          
          //cout << "board " << j << ":" << endl;
          //DumpBoard(boards[j]);
          
          // Check
          if (history.find(boards[j]) != history.end())  {
            // repeat!
            int win_player = (i + 1)% 2 + 1;
            cout << "Player " << win_player << " wins on move " << i + 1 << endl;
            solved = true;
            break;
          } 
          Rotate90(n, p);
        }
        if (!solved) {
          for (int j = 0; j < 4; ++j) 
            history.insert(boards[j]);
        }
      }
   }
    if (!solved)
      cout << "Draw" << endl;
  }
}
