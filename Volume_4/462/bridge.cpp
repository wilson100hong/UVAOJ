#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

// 2 ~ 14
int get_rank(const string& card) {
  char c = card[0];
  if (c == 'A') return 14;
  if (c == 'K') return 13;
  if (c == 'Q') return 12;
  if (c == 'J') return 11;
  if (c == 'T') return 10;
  return c - '0';
}

// S, H, D, C
int get_suit(const string& card) {
  char c = card[1];
  if (c == 'S') {
    return 0;
  } else if (c == 'H') {
    return 1;
  } else if (c == 'D') {
    return 2;
  } else { // 'C'
    return 3;
  }
}

char to_suit(int suit) {
  if (suit == 0) {
    return 'S';
  } else if (suit == 1) {
    return 'H';
  } else if (suit == 2) {
    return 'D';
  } else {
    return 'C';
  }
}

string solve(const map<int, vector<int>>& hand) {
  int score = 0, score2 = 0;
  int max_size = 0, max_suit = -1;
  int num_stopped = 0;

  for (const auto& kv : hand) {
    int size = kv.second.size();
    if (size > max_size) {
      max_suit = kv.first;
      max_size = size;
    }
    
    bool stopped = false;
    for (int rank : kv.second) {
      // 1. Each ace counts 4 points. Each king counts 3 points. Each queen counts 2 points. Each jack counts one point.
      if (rank == 14) {
        score += 4;
        // A suit is stopped if it contains an ace
        stopped = true;
      } else if (rank == 13) {
        score += 3;
        if (size == 1) {
          // 2. Subtract a point for any king of a suit in which the hand holds no other cards.
          score -= 1;
        } else {
          // A suit is stopped if it contains a king and at least one other card
          stopped = true;
        }
      } else if (rank == 12) {
        score += 2;
        if (size <= 2) {
          // 3. Subtract a point for any queen in a suit in which the hand holds only zero or one other cards.
          score -= 1;
        } else {
          // A suit is stopped if it contains a queen and at least two other cards.
          stopped = true;
        }
      } else if (rank == 11) {
        score += 1;
        // Subtract a point for any jack in a suit in which the hand holds only zero, one, or two other cards.
        if (size <= 3) {
          score -= 1;
        }
      }
    }
    if (stopped) {
      num_stopped++;
    }

    if (size == 2) {
      // 5. Add a point for each suit in which the hand contains exactly two cards.
      score2 += 1;
    } else if (size == 1) {
      // 6. Add two points for each suit in which the hand contains exactly one card.
      score2 += 2;
    } else if (size == 0) {
      // 7. Add two points for each suit in which the hand contains no cards.
      score2 += 2;
    }
  }

  // If the hand evaluates to 16 or more points ignoring rules 5, 6, and 7 and if all four suits are stopped.
  // A no trump bid is always preferred over a suit bid when both are possible.
  if (score >= 16 && num_stopped == 4) {
    return "BID NO-TRUMP";
  }
  // One may open bidding in a suit if the hand evaluates to 14 or more points. Bidding is always opened in one of the suits with the most cards
  if (score + score2 >= 14) {
    return "BID " + string(1, to_suit(max_suit));
  }
  // If the hand evaluates to fewer than 14 points, then the player must pass.
  return "PASS";
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    map<int, vector<int>> hand;
    // This is the key.. we need to add empty array for each suit!
    for (int s = 0; s < 4; ++s) {
      hand[s] = vector<int>();
    }
    for (int i = 0; i < 13; ++i) {
      string card;
      ss >> card;
      int r = get_rank(card);
      int s = get_suit(card);
      hand[s].push_back(r);
    }
    cout << solve(hand) << endl;
  }
}
