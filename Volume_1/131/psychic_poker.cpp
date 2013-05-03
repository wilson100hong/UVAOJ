#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
struct Card{
  int rank;
  char suit;
  string symbol;
};

int GetRank(char c) {
  if (c == 'A')
    return 14;
  if (c == 'T')
    return 10;
  if (c == 'J')
    return 11;
  if (c == 'Q')
    return 12;
  if (c == 'K')
    return 13;
  return c - '0';
}


string PATTERN[] = {
  "N/A",            // 0
  "highest-card",   // 1
  "one-pair",       // 2
  "two-pairs",      // 3
  "three-of-a-kind",// 4
  "straight",       // 5
  "flush",          // 6
  "full-house",     // 7
  "four-of-a-kind", // 8
  "straight-flush"  // 9
};

bool IsFlush(const vector<Card>& cards) {
  for (int i = 0; i < 4; ++i) {
    if (cards[i].suit != cards[i + 1].suit)
      return false;
  }
  return true;
}

// The following three inputs must be sorted
bool IsStraight(const vector<Card>& cards) {
  // A is fucking special case
  if (cards[0].rank == 2 &&
      cards[1].rank == 3 &&
      cards[2].rank == 4 &&
      cards[3].rank == 5 &&
      cards[4].rank == 14)
    return true;
  
  for (int i = 0; i < 4; ++i) {
    if (cards[i + 1].rank != cards[i].rank + 1)
      return false;
  }
  return true;
}

int CompareCard(const Card& c1, const Card& c2) {
  if (c1.rank == c2.rank)
    return c1.suit < c2.suit;
  else
    return c1.rank < c2.rank;
}

int GetPattern(vector<Card>& cards) {
  sort(cards.begin(), cards.end(), CompareCard);
  bool flush = IsFlush(cards);
  bool straight = IsStraight(cards);     // A is special case
 
  int cnt[15] = {0};    // TODO: make sure gcc wont jerk me
  for (int i = 0; i < 5; ++i) 
    cnt[cards[i].rank]++;

  int kind = 0;
  int pair = 0;
  for (int i = 0; i < 15; ++i) {
    kind = max(kind, cnt[i]);
    if (cnt[i] >= 2)
      pair++;
  }
  if (straight && flush) 
    return 9;
  if (kind == 4) 
    return 8;
  if (kind == 3 && pair == 2) 
    return 7;
  if (flush)
    return 6;
  if (straight)
    return 5;
  if (kind == 3)
    return 4;
  if (pair == 2)
    return 3;
  if (pair == 1)
    return 2;
  return 1;

}

void GetHand(int seq,
             const vector<Card>& given,
             const vector<Card>& deck,
             vector<Card>& hand) {
  hand.clear();
  int remain = 5;
  for (int i = 0; i < 5; ++i) {
    if ((seq >> i) & 1) {
      hand.push_back(given[i]);
      remain--;
    }
  }
  int j = 0;
  while (remain-- > 0)
    hand.push_back(deck[j++]);
}

void DumpHand(const vector<Card>& hand) {
  for (int i = 0; i < 5; ++i)
    cout << hand[i].symbol << " ";
  cout << endl;
}


using namespace std;

int main() {
  string line, symbol;
  vector<Card> given;
  vector<Card> deck;
  vector<Card> hand;
  Card card;
  while (getline(cin, line)) {
    given.clear();
    deck.clear();
    stringstream ss(line);
    
    cout << "Hand:";
    for (int i = 0; i < 5; ++i) {
      ss >> symbol;
      card.symbol = symbol;
      card.suit = symbol[1];
      card.rank = GetRank(symbol[0]);
      given.push_back(card);
      cout << " " << symbol;
    }
    cout << " Deck:";
    for (int i = 0; i < 5; ++i) {
      ss >> symbol;
      card.symbol = symbol;
      card.suit = symbol[1];
      card.rank = GetRank(symbol[0]);
      deck.push_back(card);
      cout << " " << symbol;
    }
    cout << " Best hand: ";
    int best = 0;
    for (int i = 0; i < 32; ++i) {
      GetHand(i, given, deck, hand);
      //DumpHand(hand);
      best = max(best, GetPattern(hand));
    }
    cout << PATTERN[best] << endl;
  }
}
