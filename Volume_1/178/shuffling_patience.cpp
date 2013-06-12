#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

/**
 * Maybe the hardest part is to understand the problem description :)
 * The problem sample is actually very easy, it just means "8S" and
 * "3H" cancel each other, and we replace "8S" with "KH" and "3H" with "9H".
 * 
 * Trick:
 * 1. When there are both pair and triples, use the one with "minimum start card index".
 * 2. Watch out when overflowed, print the "card about to be deal".
 *
 */
using namespace std;
struct Card{
  char suit;
  int rank;
};

int r2i(char rank) {
   if (rank == 'A')
      return 1;
   if (rank == 'T')
      return 10;
   if (rank == 'J')
      return 11;
   if (rank == 'Q')
      return 12;
   if (rank == 'K')
      return 13;
   return (int) (rank - '0');
}

#define N_CARD 52
#define N_PILE 16
#define NOFOUND 99
int main() {
   string line;
   string lines;
   vector<Card> deck;
   stack<Card> piles[N_PILE];
   int round = 1;

   while (getline(cin, line) && line != "#") {
      lines = line;
      for (int i = 0; i < 3; ++i) {
         getline(cin, line);
         lines = lines + " " + line;
      }        

      stringstream ss(lines);
      deck.clear();
      for (int i = 0; i < N_CARD; ++i) {
         string cs; // card string
         ss >> cs;
         Card card = {cs[1], r2i(cs[0])}; 
         deck.push_back(card);
      }
      
      Card card;
      // clear piles
      for (int i = 0; i < N_PILE; ++i) {
         while(!piles[i].empty()) 
            piles[i].pop();
      }
  
      // Do simulation
      int pile = 0, dealed = 0;
      queue<int> covered;
      
      while (dealed < N_CARD && pile < N_PILE) {
         Card card = deck[dealed];
         piles[pile].push(card);
         dealed++;

         while (dealed < N_CARD) {
            if (covered.empty()) {
               bool has_pair = false, has_triple = false;
               int pair[2] = {NOFOUND, NOFOUND};
               int triple[3] = {NOFOUND, NOFOUND, NOFOUND};

               // Pair?
               for (int start = 0; start < pile; ++start) {
                  int n0 = piles[start].top().rank;
                  if (n0 <= 10) {
                     for (int end = start + 1; end <= pile; ++end) {
                        int n1 = piles[end].top().rank;
                        if (n0 + n1 == 11) {
                           pair[0] = start;
                           pair[1] = end;
                           break;
                        }
                     }
                  }
                  if (pair[0] != NOFOUND && pair[1] != NOFOUND) {
                     has_pair = true;
                     break;
                  }
               }

               // Triple?
               for (int start = 0; start <= pile; ++start) {
                  int s0 = piles[start].top().rank - 11;
                  if (triple[s0] == NOFOUND) {
                     triple[s0] = start;
                     if (triple[0] != NOFOUND && triple[1] != NOFOUND && triple[2] != NOFOUND) {
                        has_triple = true;
                        // sort
                        if (triple[0] > triple[1]) swap(triple[0], triple[1]);
                        if (triple[1] > triple[2]) swap(triple[1], triple[2]);
                        if (triple[0] > triple[1]) swap(triple[0], triple[1]);
                        break;
                     }
                  }
               }

               if (has_pair || has_triple) {
                  bool use_pair = (has_pair && (!has_triple || pair[0] < triple[0]));
                  if (use_pair) {
                     covered.push(pair[0]);
                     covered.push(pair[1]);
                  } else {
                     covered.push(triple[0]);
                     covered.push(triple[1]);
                     covered.push(triple[2]);
                  }
               } else {
                  // no need to cover cards
                  break;
               }
            } else {
               // deal a card every time
               Card ac = deck[dealed];
               piles[covered.front()].push(ac);
               covered.pop();  
               dealed++;
            }
         }
         pile++;
      }

      cout.width(3);
      cout << round << ":";
      if (dealed == N_CARD) {
         for (int i = 0; i < N_PILE; ++i) {
            if (piles[i].empty())
               break;
            cout.width(3);
            cout << piles[i].size();
         }
      } else {
         cout << " Overflowed on card no";
         cout.width(3);
         cout << dealed + 1;
      }
      cout << endl;

      round++;
   }
}
