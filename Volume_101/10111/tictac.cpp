#include <iostream>
#include <map>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

// we use string to represent board
#define EMPTY_BOARD "................"
#define X 'x'
#define O 'o'
#define EMPTY '.'

// result
typedef int Result;
#define UNKNOWN 0
#define WIN 1
#define LOSE 2
#define DRAW 3

#define ANY_MOVE -1
struct Strategy{
  Result result;
  // the desired move to make to achieve best result.
  // If result is LOSE, it will be ANY_MOVE
  int move;
};

map<string, Strategy> strategies;  // board -> strategy (for X and O, depends on who's turn)
vector<vector<int>> lines;  // all possible lines in the board

int index(int r, int c) { return r * 4 + c; }

string dump(int move) {
  int r = move / 4;
  int c = move % 4;
  stringstream ss;
  ss << "(" << r << "," << c << ")";
  return ss.str();
}

// initialize lines
void build_lines() {
  // 1. scan ROW
  for (int r = 0; r < 4; ++r) {
    vector<int> line; 
    for (int c = 0; c < 4; ++c) {
      line.push_back(index(r, c));
    }
    lines.push_back(line);
  }
  // 2. scan COLUMN
  for (int c = 0; c < 4; ++c) {
    vector<int> line; 
    for (int r = 0; r < 4; ++r) {
      line.push_back(index(r, c));
    }
    lines.push_back(line);
  }
  // 3. scan DIAGONAL
  {
    vector<int> line;
    for (int r = 0, c = 0; r < 4 && c < 4; r++, c++) {
      line.push_back(index(r, c));
    }
    lines.push_back(line);
  }
  {
    vector<int> line;
    for (int r = 0, c = 3; r < 4 && c >= 0; r++, c--) {
      line.push_back(index(r, c));
    }
    lines.push_back(line);
  }

  //for (vector<int>& line : lines) {
    //for (int x : line) {
      //cout << x << ",";
    //}
    //cout << endl;
  //}
}

char get_opponent(char player) {
  if (player == X) return O;
  if (player == O) return X;
  return '?';
}

// judge if the game is over. If so, return game result either WIN, LOSE or DRAW
// otherwise return UNKNOWN
// player: player's turn
// wm: winning moves. make that move then the player will win. Only meaningful for UNKNOWN
// lm: losing moves. the oppenent will win if he make that move. Only meaningful for UNKNOWN
Result judge(const string& board, char player,
    set<int>& wm, set<int>& lm) {
  wm.clear();
  lm.clear();
  char oppenent = get_opponent(player);
  int cd = 0;  // count of draw lines
  for (const vector<int>& line : lines) {
    int cp = 0, co = 0;  // player / opponent
    int any_empty = ANY_MOVE;
    for (int index : line) {
      if (board[index] == player) {
        cp++;
      } else if (board[index] == oppenent) {
        co++;
      } else {
        any_empty = index;
      }
    }
    if (cp == 4) return WIN;
    if (co == 4) return LOSE;
    if (cp > 0 && co > 0) {
      cd++;
    } else if (cp == 3 && co == 0) {
      wm.insert(any_empty);
    } else if (co == 3 && cp == 0) {
      lm.insert(any_empty);
    }
  }
  if (cd == 10) return DRAW;
  return UNKNOWN;
}

Strategy think(const string& board, char player, set<int>& wm, set<int>& lm) {
  if (strategies.count(board) == 0) {
    int result = judge(board, player, wm, lm);
    return {result, ANY_MOVE};
  }
  return strategies[board];  // all Strategy in strategies has certain result.
}

Strategy turn(const string& board, char player) {
  set<int> wm, lm;
  Strategy s = think(board, player, wm, lm);
  if (s.result != UNKNOWN) {
    return s;
  }

  if (wm.size() > 0) {
    // will win
    strategies[board] = {WIN, *wm.begin()};
  } else if (lm.size() > 1) {
    // must lose
    strategies[board] = {LOSE, ANY_MOVE};
  } else {
    vector<int> moves;  // candidate moves
    if (lm.size() == 1) {
      // to avoid lose, must take this move
      moves.push_back(*lm.begin());
    } else {
      for (int move = 0; move < 16; ++move) {
        if (board[move] == EMPTY) {
          moves.push_back(move);
        }
      }
    }
    strategies[board] = {LOSE, ANY_MOVE};
    for (int move : moves) {
      string nb(board);
      nb[move] = player;
      Strategy ns = turn(nb, get_opponent(player));

      if (ns.result == LOSE) {
        // opponent lose anyway
        strategies[board] = {WIN, move};
        break;
      } else if (ns.result == DRAW) {
        strategies[board] = {DRAW, move};
      } else if (ns.result == WIN) {
        ;
      }
    }
  }
  return strategies[board];
}

int main() {
  build_lines();
  char c;
  while (1) {
    cin >> c;
    if (c == '$') break;
    if (c != '?') break;  // should not happen
    string board(EMPTY_BOARD);
    for (int i = 0; i < 16; ++i) {
      cin >> c;
      board[i] = c;
    }

    set<int> wm, lm;
    Result result = judge(board, X, wm, lm);
    if (result != UNKNOWN || lm.size() > 1) {
      cout << "#####" << endl;  // game is over
      continue;
    }
    
    vector<int> moves;
    if (lm.size() == 1) {
      // to avoid lose, must take this move
      if (wm.size() > 0) {
        moves.push_back(*wm.begin());
      } else {
        moves.push_back(*lm.begin());
      }
    } else {
      for (int move = 0; move < 16; ++move) {
        if (board[move] == EMPTY) {
          moves.push_back(move);
        }
      }
    }
    bool has_wining_move = false;
    for (int move : moves) {
      string nb(board);
      nb[move] = X;
      Strategy ns = turn(nb, O);

      if (ns.result == LOSE) {
        // opponent lose anyway
        cout << dump(move) << endl;
        has_wining_move = true;
        break;
      }
    }
    if (!has_wining_move) {
      cout << "#####" << endl;  // no winning move
    }
  }
}
