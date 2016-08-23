// Need optimization
// TODO: optimize
// 1) try using prioirty queue?
// 2) optimize for all simple calculation
// 3) review A*
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>
#include <tuple>
#include <vector>

namespace std
{
  template<typename T, size_t N>
    struct hash<array<T, N> >
    {
      typedef array<T, N> argument_type;
      typedef size_t result_type;

      result_type operator()(const argument_type& a) const
      {
        hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < N; ++i)
        {
          h = h * 31 + hasher(a[i]);
        }
        return h;
      }
    };
}

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
    //int dist = board[i] == 0 ? distance(i, 15): distance(i, board[i]-1);
    int dist = distance(i, board[i]-1);
    manhatan += dist;
  }
  // TODO: this will improve the computation speed, but the answer will not be optimal
  return 3*manhatan / 2;
  //return 4*manhatan/3;
  //return manhatan;
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
int invert_dir(int dir) {
  if (dir == 0) return 1;
  if (dir == 1) return 0;
  if (dir == 2) return 3;
  if (dir == 3) return 2;
}

int dr[4] = {0, 0, -1, 1};  // row
int dc[4] = {1, -1, 0, 0};  // col
// return (0, _) for sccuess and (-1, _) for failed
pair<int, Board> get_new_board(const Board& board, int dir) {
  // print_board(board);
  int mr, mc;
  int mindex = get_index(board, 0);
  tie(mr, mc) = get_rc(mindex);

  int nr = mr + dr[dir];
  int nc = mc + dc[dir];
  if (nr < 0 || nr > 3 || nc < 0 || nc > 3) {
    return {-1, board};
  }

  int nindex = nr*4 + nc;
  // swap missing with the neighbor
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
  unordered_map<Board, int> g;  // steps used so far
  unordered_map<Board, int> h;  // steps heuristic
  unordered_map<Board, int> f;  // f = g + h
  unordered_map<Board, int> prev;
  unordered_set<Board> closed;

  g[board] = 0;
  h[board] = heuristic(board);
  f[board] = g[board] + h[board];
  
  heap.insert(IB(g[board] + h[board], board));

  while (!heap.empty()) {
    IB top = *(heap.begin());
    heap.erase(top);
    Board cur_board = top.second;

    if (closed.count(cur_board)) {
      cout << "board appears multiple times in closed set" << endl;
      return;
    }
    closed.insert(cur_board);
    
    
    /*
    // cout << "F: " << top.first << endl;
    if (top.first < last_f) {
      cout << "f decrease!" << endl;
    }
    last_f = top.first;
    */

    /*
    if (h[cur_board] == 0) {
      // cout << "found" << endl;
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
    */

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
      // TODO: not sure
      // it turns out does not matter
      if (closed.count(new_board) != 0) {
        continue;
      }

      int ng = g[cur_board] + 1;
      int nh = heuristic(new_board);
      if (nh == 0) {
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
        cout << ops[delta];
        cout << endl;
        return;
      }

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
      prev[new_board] = delta;

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
