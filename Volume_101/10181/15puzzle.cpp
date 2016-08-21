// Need optimization
// 1. review A* update policy
// 2. better heuristic?
// 3. use IDA*
#include <array>
#include <iomanip>
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

typedef array<int, 16> Board;

void print_board(const Board& board) {
  for (int i = 0; i < 16; ++i) {
    cout << setw(3);
    cout << board[i] << " ";
    if (i % 4 == 3) {
      cout << endl;
    }
  }
}

int heuristic(const Board& board) {
  // manhatan distance execpt '0'
  int manhatan = 0;
  for (int i=0; i<16; ++i) {
    if (board[i] == 0) 
      continue;
    int dist = distance(i, board[i]-1);
    manhatan += dist;
  }
  // TODO: this will improve the computation speed, but the answer will not be optimal
  return 4*manhatan / 3;
}

int get_index(const Board& board, int num) {
  for (int i = 0; i < 16; ++i) {
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
// return (0, _) for sccuess and (-1, _) for failed
pair<int, Board> get_new_board(const Board& board, int delta) {
  // print_board(board);
  int mr, mc;
  int mindex = get_index(board, 0);
  tie(mr, mc) = get_rc(mindex);

  int nr = mr + dr[delta];
  int nc = mc + dc[delta];
  if (nr < 0 || nr > 3 || nc < 0 || nc > 3) {
    return {-1, board};
  }

  int nindex = nr*4 + nc;
  // swap
  // TODO: make sure copy works
  Board nb = board;
  nb[nindex] = 0;  // board[mindex];
  nb[mindex] = board[nindex];
  return {0, nb};
}

int MAX_STEPS = 50;
typedef pair<int, Board> IB;

// A*
void solve(const Board& board) {
  set<IB> heap;
  map<Board, int> g;  // steps used so far
  map<Board, int> h;  // steps heuristic
  map<Board, int> f;  // f = g + h
  map<Board, pair<char, Board>> prev;

  g[board] = 0;
  h[board] = heuristic(board);
  f[board] = g[board] + h[board];
  
  heap.insert(IB(f[board], board));

  int last_f = f[board];
  while (!heap.empty()) {
    IB top = *(heap.begin());
    heap.erase(top);
    Board cur_board = top.second;
    
    /*
    // cout << "F: " << top.first << endl;
    if (top.first < last_f) {
      cout << "f decrease!" << endl;
    }
    last_f = top.first;
    */

    if (h[cur_board] == 0) {
      // found it, reconstruct moves
      vector<char> moves;
      while (prev.count(cur_board) != 0) {
        moves.push_back(prev[cur_board].first);
        cur_board = prev[cur_board].second;
      }
      for (int i = moves.size()-1; i >= 0; --i) {
        cout << moves[i];
      }
      cout << endl;
      return;
    }

    if (g[cur_board] > MAX_STEPS)
      continue;
    /*
    if (f[cur_board] > MAX_STEPS) 
      break;
    */

    // for all successors
    for (int delta = 0; delta < 4; ++delta) {
      int code;
      Board new_board;
      tie(code, new_board) = get_new_board(cur_board, delta);
      if (code < 0) {
        continue;
      }

      int ng = g[cur_board] + 1;
      int nh = heuristic(new_board);
      int nf = ng + nh;

      /*
      if (nf > MAX_STEPS) {
        continue;
      }
      */

      if (f.count(new_board) != 0 && nf >= f[new_board]) {
        // not better
        continue;
      }

      // update f, g, h for new_board
      // TODO: figure out why g could decrease?
      if (f.count(new_board) != 0) {
        // cout << "Erase happen" << endl;

        /*
        cout << "Board: " << endl;
        print_board(new_board);
        cout << "Cur f=" << top.first << endl;
        cout << "Old f=" << f[new_board] << endl;
        cout << "Old g=" << g[new_board] << endl;
        cout << "Old h=" << h[new_board] << endl;

        // print old moves
        cout << "Old moves: ";
        vector<char> moves;
        Board t_board(new_board);
        while (prev.count(t_board) != 0) {
          moves.push_back(prev[t_board].first);
          t_board = prev[t_board].second;
        }
        for (int i = moves.size()-1; i >= 0; --i) {
          cout << moves[i];
        }
        cout << endl;

        cout << "New f=" << nf << endl;
        cout << "New g=" << ng << endl;
        cout << "New h=" << nh << endl;

        // print new moves
        cout << "New moves: ";
        Board tt_board(cur_board);
        moves.clear();
        while (prev.count(tt_board) != 0) {
          moves.push_back(prev[tt_board].first);
          tt_board = prev[tt_board].second;
        }
        for (int i = moves.size()-1; i >= 0; --i) {
          cout << moves[i];
        }
        cout << ops[delta];
        cout << endl;
        */
        
        // remove old one
        heap.erase(IB(f[new_board], new_board));
      }

      f[new_board] = nf;
      g[new_board] = ng;
      h[new_board] = nh;
      prev[new_board] = {ops[delta], cur_board};

      heap.insert(IB(nf, new_board));

      /*
      if (prev.count(cur_board) != 0) {
        char last1 = ops[delta];
        char last2 = prev[cur_board].first;
        if ((last1 == 'U' && last2 == 'D') ||
            (last1 == 'D' && last2 == 'U') ||
            (last1 == 'L' && last2 == 'R') ||
            (last1 == 'R' && last2 == 'L')) {
          cout << "YOU SON OF BITCH" << endl;
        }
      }
      */
    }
  }
  cout << "This puzzle is not solvable." << endl;
}

bool impossible(const Board& board) {
  int sum = 0;
  vector<bool> visit(16, false);
  for (int i = 0; i < 16; ++i) {
    int n = board[i];
    if (n == 0) {
      int r, c;
      tie(r, c) = get_rc(i);
      sum += (r + 1);
    } else {
      for (int j = 1; j < n; ++j) {
        if (!visit[j]) {
          sum++;
        }
      }
    }
    visit[n] = true;
  }
  return sum % 2 != 0;
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds--) {
    Board board;
    for (int i = 0; i < 16;  ++i) {
      cin >> board[i];
    }
    if (impossible(board)) {
      cout << "This puzzle is not solvable." << endl;
    } else {
      solve(board);
    }
  }
}
