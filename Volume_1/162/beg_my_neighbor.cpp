#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;
enum Player{NonDealer = 0, Dealer };

bool isFace(string card) {
  char c = card[1];
  return c == 'A' || c == 'K' || c == 'Q' || c == 'J';
}

int Debt(string card) {
  char c = card[1];
  if (c == 'A')
    return 4;
  if (c == 'K')
    return 3;
  if (c == 'Q')
    return 2;
  if (c == 'J')
    return 1;
  return 1;
}

int main() {
  string line;
  string input = "";
  stack<string> cards[2];
  stack<string> heap;

  while (getline(cin, line)) {
    if (line == "#")
      break;
    input = line;
    for (int i = 0; i < 3; ++i) {
      getline(cin, line);
      input += (" " + line);
    }
    // Initialize
    int player = NonDealer;
    while (!cards[NonDealer].empty())
      cards[NonDealer].pop();
    while (!cards[Dealer].empty())
      cards[Dealer].pop();
    while (!heap.empty())
      heap.pop();

    // Dispatch cards
    stringstream ss(input);
    string card;
    for (int i = 0; i < 52; ++i) {
      ss >> card;
      cards[player++].push(card);
      player %= 2;
    }

    player = NonDealer;
    int debt = 1;
    bool game_over = false;
    bool in_sequence = false;
    // Game begins
    while (1) {
      bool draw_face = false;
      while (debt > 0) {
        if (cards[player].empty()) {
          // Game Over
          game_over = true;
          break;
        }
        // player face a card
        card = cards[player].top();
        cards[player].pop();
        heap.push(card);
        debt--;

        // When draw a face card
        if (isFace(card)) {
          draw_face = true;
          break;
        }
      }

      debt = Debt(card);
      player = (player + 1) % 2;
      if (game_over) {
        cout << (player == 0 ? 2 : 1);
        cout.width(3);
        cout << cards[player].size() << endl;
        break;
      } else if (draw_face) {
        in_sequence = true;
      } else if (in_sequence) { // no face draw this round.
        // If in sequence, player place all cards in heap face down under his deck.
        // // TODO:
        stack<string> tmp;

        while (!heap.empty()) {
          // TODO: order might be wrong
          tmp.push(heap.top());
          heap.pop();
        }
        // keep deck's order, so double stack trick
        while (!cards[player].empty()) {
          heap.push(cards[player].top());
          cards[player].pop();
        }
        while (!heap.empty()) {
          tmp.push(heap.top());
          heap.pop();
        }
        cards[player] = tmp;
        in_sequence = false;
        // heap should be empty here
      }
    }
  }
}
