#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <tuple>
#include <vector>
using namespace std;

int abs(int x) {
  return x > 0 ? x : -x;
}

int distance(int index1, int index2) {
  int r1 = index1 / 4;
  int c1 = index1 % 4;
  int r2 = index2 / 4;
  int c2 = index2 % 4;
  return abs(r1-r2) + abs(c1-c2);
}
typedef vector<int> Board;

void print_board(const Board& board) {
  for (int i = 0; i < 16; ++i) {
    cout << board[i] << " ";
    if (i % 4 == 3) {
      cout << endl;
    }
  }
  cout << "---------" << endl;
}

int get_index(const Board& board, int num) {
  for (int i = 0; i < board.size(); ++i) {
    if (board[i] == num)
      return i;
  }
  return -1;  // should never happen
}

pair<int, int> get_rc(int index) {
  int r = index / 4;
  int c = index % 4;
  return {r, c};
}

char ops[4] = {'R', 'L', 'U', 'D'};
int dr[4] = {0, 0, -1, 1};  // row
int dc[4] = {1, -1, 0, 0};  // col

int op2delta(char op) {
  if (op == 'R') 
    return 0;
  if (op == 'L')
    return 1;
  if (op == 'U')
    return 2;
  if (op == 'D')
    return 3;
  return -1;  // you are fukced
}

int heuristic(const Board& board) {
  // manhatan distance execpt '0'
  int cost = 0;
  for (int i= 0; i< 16; ++i) {
    if (board[i] == 0) 
      continue;
    int expect_index = board[i]-1;
    int dist = distance(i, expect_index);
    cost += dist;
  }
  return cost;
}

void sim(Board& board, const string& moves) {
  cout << "start!" << endl;
  print_board(board);
  cout << "H: " << heuristic(board) << endl;
  int G = 0;
  for (char op : moves) {
    int mr, mc;
    int mindex = get_index(board, 0);
    tie(mr, mc) = get_rc(mindex);
    int delta = op2delta(op);
    int nr = mr + dr[delta];
    int nc = mc + dc[delta];
    int nindex = nr*4 + nc;
    board[mindex] = board[nindex];
    board[nindex] = 0;
    print_board(board);

    int H = heuristic(board);
    cout << "H: " << H << endl;
    cout << "F: " << G + H << endl;
    G++;
  }
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds--) {
    Board board;
    for (int i = 0; i < 16;  ++i) {
      int cell;
      cin >> cell;
      board.push_back(cell);
    }
    // string moves = "UULURDRDDLLUURURDLDRRULLULDDRRULLDRRRDLLURRULDDR";
    string moves = "UURDDLURRDLLLUURRULLDDRRRULLLDRUURDDRDLULDRRULLDRR";
    sim(board, moves);
    /*
    string m = "LUURRD";
    sim(board, m);
    cout << "======================" << endl;

    Board b1(board);
    Board b2(board);
    // string m1 = "LUURRDLDRULDR";
    // string m2 = "LUURRDDLURD";
    string m1 = "LDRULDR";
    sim(b1, m1);
    cout << "----------------------" << endl;
    string m2 = "DLURD";
    sim(b2, m2);
    cout << "----------------------" << endl;
    */
  }
}
