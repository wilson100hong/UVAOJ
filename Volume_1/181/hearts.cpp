#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int trump = -1;
int specify = -1;

int value2Int(char value) {
   if (value == 'A')
      return 14;
   else if (value == 'K')
      return 13;
   else if (value == 'Q')
      return 12;
   else if (value == 'J')
      return 11;
   else if (value == 'T')
      return 10;
   else  // 2 ~ 9
      return (int) (value - '0');
}

char int2Value(int value) {
   if (value == 10)
      return 'T';
   if (value == 11)
      return 'J';
   if (value == 12)
      return 'Q';
   if (value == 13)
      return 'K';
   if (value == 14)
     return 'A';
   return (char) (value + '0');
}

int suite2Int(char suite) {
   switch(suite) {
      case 'C':
         return 1;
      case 'D':
         return 2;
      case 'H': 
         return 3;
      case 'S':
         return 4;
      default:
         return -1;
   }
}

char int2Suite(int suite) {
   if (suite == 1)
      return 'C';
   if (suite == 2)
      return 'D';
   if (suite == 3)
      return 'H';
   if (suite == 4)
      return 'S';
   return -1;
}
struct Card{
   int suite; // 1 ~ 4
   int value; // 2 ~ 13
};

void DumpCard(const Card& card) {
   cout << int2Value(card.value) << int2Suite(card.suite);
}

#define NUM_PLAYERS 5

// return 1 if card1 < card2
bool CardLessIgnoreTrump(const Card& card1, const Card& card2) {
   if (card1.value == card2.value)
      return card1.suite < card2.suite;
   else
      return card1.value < card2.value;
}

bool CardLess(const Card& card1, const Card& card2) {
   if (card1.value == card2.value)  {
      if (card1.suite == trump) 
         return false; // card1 > card2
      if (card2.suite == trump)
         return true;
      return card1.suite < card2.suite;
   }
   return card1.value < card2.value;
}

bool CardLessWithTrump(const Card& card1, const Card& card2) {
   if (card1.suite == trump && card2.suite == trump) {
     return card1.value < card2.value;
   } else if (card1.suite == trump) {
      return false;  // card1 > card2
   } else if (card2.suite == trump) {
      return true;
   } else {   // card1.suite != trump && card2.suite != trump
      return CardLessIgnoreTrump(card1, card2);
   }
}

bool CardLessWithSpecifyTrump(const Card& card1, const Card& card2) {
   if (card1.suite == specify && card2.suite == specify) {
      return card1.value < card2.value;
   } else if (card1.suite == specify) {
      return false;  // card1 > card2
   } else if (card2.suite == specify) {
      return true;
   } else {  // card1.suite != specify && card2.suite != specify
      return CardLessWithTrump(card1, card2);
   }
}

bool CardLessWithTrumpSpecify(const Card& card1, const Card& card2) {
   if (card1.suite == trump && card2.suite == trump) {
      return card1.value < card2.value;
   } else if (card1.suite == trump) {
      return false;  // card1 > card2
   } else if (card2.suite == trump) {
      return true;
   } else { //  card1.suite != trump && card2.suite != trump
      return CardLessWithSpecifyTrump(card1, card2);
   }
}

bool PairLessWithTrumpSpecify(const pair<Card, int>& p1, const pair<Card, int>& p2) {
  return CardLessWithTrumpSpecify(p1.first, p2.first);
}

void Solve(string input) {
   vector<Card> players[NUM_PLAYERS];   // 0 is dealer
   vector<Card> gains[NUM_PLAYERS];
   // Clear players' hands and gains
   for (int i = 0; i < NUM_PLAYERS; ++i) {
      players[i].clear();
      gains[i].clear();
   }
   // Reset trump to undefined
   trump = -1;
   // Dispatch cards
   stringstream ss(input);
   string card_str;
   Card card;
   for (int i = 0; i < 50; ++i) {
      ss >> card_str;
      card.value = value2Int(card_str[0]);
      card.suite = suite2Int(card_str[1]);
      // Start from the player left of dealer
      players[(i + 1) % NUM_PLAYERS].push_back(card);
   }
   // Determine the trump
   Card rest[2];
   for (int i = 0; i < 2; ++i) {
      ss >> card_str;
      rest[i].value = value2Int(card_str[0]);
      rest[i].suite = suite2Int(card_str[1]);
   }
   if (CardLessIgnoreTrump(rest[0], rest[1])) 
      trump = rest[1].suite;
   else
      trump = rest[0].suite;

   //cout << "Trump is: " << trump << endl;
  
   int leader = 1;
   vector<pair<Card, int> > hands;
   for (int trick = 0; trick < 10; ++trick) {
      hands.clear();
      // Leader plays card
      sort(players[leader].begin(), players[leader].end(), CardLess);
      pair<Card, int> p(players[leader].back(), leader);
      hands.push_back(p);
      players[leader].pop_back();

      specify = hands[0].first.suite;
      //cout << "SPECIFY: " << specify << endl;
      // Followers play cards
      for (int i = 1; i < NUM_PLAYERS; ++i) {
         int player = (leader + i) % NUM_PLAYERS;
         // Pick the highest card as specify, than trump
         sort(players[player].begin(), players[player].end(), CardLessWithSpecifyTrump);      
         pair<Card, int> p(players[player].back(), player);
         hands.push_back(p);
         players[player].pop_back();
      }
      sort(hands.begin(), hands.end(), PairLessWithTrumpSpecify);
      leader = hands.back().second;
      for (int i = 0; i < NUM_PLAYERS; ++i)
         gains[leader].push_back(hands[i].first);
   }

   // Count the score
   for (int i = 0; i < NUM_PLAYERS; ++i) {
      int score = 0;
      for (int j = 0; j < gains[i].size(); ++j) {
         if (gains[i][j].suite == 3) 
            score += gains[i][j].value;
      }
      cout.width(3);
      cout << score;
   }
   cout << endl;

}

int main() {
   string line;
   string input;
   
   while (getline(cin, line) && line != "#") {
      input = line;
      for (int i = 0; i < 3; ++i) {
         getline(cin, line);
         input = input + " " + line;
      }
      Solve(input);
   }
}

