// Optimizations I did: 
// 1. in A*, for nodes in open or closed set, compare "g" function instead of "f"
// 2. use "unordered_map" instead of "map" for g/h/f lookup. Its O(1) v.s. O(logN)
// 3. use "unsigned long int" to represent the puzzle state instead of of
//    using vector or array to avoid expensive hashing.
// 4. the heurisitc function I used is h(x) = 3*manhantan/2, but using integer
//    division will lose percision because of flooring. Ideally we should use double,
//    but I am lazy so I just let f(x) = 3*g(x) + 2*h(x)
// 5. early exit when g(x) + h(x) > MAX_STEPS
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>
#include <tuple>
#include <vector>

using namespace std;

int abs(int x) {
  return x > 0 ? x : -x;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int distance(int index1, int index2) {
  int r1 = index1 / 4;
  int c1 = index1 % 4;
  int r2 = index2 / 4;
  int c2 = index2 % 4;
  return abs(r1-r2) + abs(c1-c2);
}

typedef unsigned long int Tile;
typedef unsigned long int Board;

void print_board(Board board) {
  for (int i = 0; i < 16; ++i) {
    Tile tile = (board & 15);
    board = board >> 4;
    cout << setw(3);
    cout << tile;
    if (i % 4 == 3) {
      cout << endl;
    }
  }
}

int heuristic(Board board) {
  // manhatan distance execpt '0'
  int manhatan = 0;
  for (int i=0; i<16; ++i) {
    Tile tile = (board & 15);
    board = board >> 4;
    if (tile == 0)
      continue;
    //int dist = board[i] == 0 ? distance(i, 15): distance(i, board[i]-1);
    int dist = distance(i, tile-1);
    manhatan += dist;

  }
  return manhatan;
}

int get_index(Board board, int num) {
  for (int i = 0; i < 16; ++i) {
    Tile tile = (board & 15);
    board = board >> 4;
    if (tile == num)
      return i;
  }
  return -1;  // should never happen
}

pair<int, int> get_rc(int index) {
  int r = index / 4;
  int c = index % 4;
  return {r, c};
}

//char ops[4] = {'R', 'L', 'U', 'D'};
char ops[4] = {'D', 'U', 'R', 'L'};
int invert_dir(int dir) {
  if (dir == 0) return 1;
  if (dir == 1) return 0;
  if (dir == 2) return 3;
  if (dir == 3) return 2;
}

Board set_board_index(Board board, int index, Tile tile) {
  unsigned long int mask = ((1UL<<4)-1) << (index*4);
  board &= ~mask;
  board |= ( (tile<<(index*4)) & mask);
  return board;
}

int dr[4] = {1, -1, 0, 0};  // row
int dc[4] = {0, 0, 1, -1};  // col
// return (0, _) for sccuess and (-1, _) for failed
pair<int, Board> get_new_board(Board board, int dir) {
  int mindex = get_index(board, 0);
  int mr, mc;
  tie(mr, mc) = get_rc(mindex);

  int nr = mr + dr[dir];
  int nc = mc + dc[dir];
  if (nr < 0 || nr > 3 || nc < 0 || nc > 3) {
    return {-1, board};
  }

  int nindex = nr*4 + nc;
  Tile tile = ((board>>(4*nindex)) & 15);
  // swap missing with the neighbor
  board = set_board_index(board, mindex, tile);
  board = set_board_index(board, nindex, 0);
  return {0, board};
}

int MAX_STEPS = 50;
typedef pair<int, Board> IB;

// A*
void solve(const Board& board) {
  set<IB> heap;
  unordered_set<Board> closed;
  unordered_map<Board, int> g;  // steps used so far
  unordered_map<Board, int> h;  // steps heuristic
  unordered_map<Board, int> f;  // f = 2*g + 3*h
  unordered_map<Board, int> prev;

  g[board] = 0;
  h[board] = heuristic(board);
  f[board] = 2*g[board] + 3*h[board];
  
  heap.insert(IB(f[board], board));

  int cnt = 0;
  while (!heap.empty()) {
    cnt++;

    IB top = *(heap.begin());
    Board cur_board = top.second;
    heap.erase(top);

    closed.insert(cur_board);

    if (h[cur_board] == 0) {
      // found it, reconstruct moves 
      vector<char> moves;
      while (prev.count(cur_board) != 0) {
        moves.push_back(prev[cur_board]);
        int dummy;
        tie(dummy, cur_board) = get_new_board(cur_board, invert_dir(prev[cur_board]));
      }
      for (int i = moves.size()-1; i >= 0; --i) {
        cout << ops[moves[i]];
      }
      cout << endl;
      return;
    }

    if ((g[cur_board] + h[cur_board]) > MAX_STEPS)
      continue;

    // for all successors
    for (int dir = 0; dir < 4; ++dir) {
      int code;
      Board new_board;
      tie(code, new_board) = get_new_board(cur_board, dir);
      if (code < 0) {
        continue;
      }

      int ng = g[cur_board] + 1;
      if (closed.count(new_board) > 0) {
        // in close set
        if (g[new_board] > ng) {
          closed.erase(new_board);
        } else {
          continue;
        }
      } else if (g.count(new_board) > 0) {
        // in open set
        if (g[new_board] > ng) {
          heap.erase(IB(f[new_board], new_board));
        } else {
          continue;
        }
      }

      int nh = heuristic(new_board);
      int nf = 2*ng + 3*nh;

      f[new_board] = nf;
      g[new_board] = ng;
      h[new_board] = nh;
      prev[new_board] = dir;

      parent_cnt[new_board] = cnt;
      heap.insert(IB(nf, new_board));
    }
  }
  cout << "This puzzle is not solvable." << endl;
}

bool impossible(Board board) {
  int sum = 0;
  vector<bool> visit(16, false);
  for (int i = 0; i < 16; ++i) {
    Tile tile = board & 15;
    board = board >> 4;
    if (tile == 0) {
      int r, c;
      tie(r, c) = get_rc(i);
      sum += (r + 1);
    } else {
      for (int j = 1; j < tile; ++j) {
        if (!visit[j]) {
          sum++;
        }
      }
    }
    visit[tile] = true;
  }
  return sum % 2 != 0;
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds--) {
    Board board = 0;
    for (int i = 0; i < 16;  ++i) {
      Tile tile;
      cin >> tile;
      board |= (tile << (4*i));
    }
    if (impossible(board)) {
      cout << "This puzzle is not solvable." << endl;
    } else {
      solve(board);
    }
  }
}
