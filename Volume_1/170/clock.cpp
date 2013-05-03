#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;

struct Card{
  char rank;  // A ~ K
  char suit;  // H, D, C, S
};

map<char, int> rank_map;

void InitRankMap() {
  rank_map['A'] = 0;
  rank_map['2'] = 1;
  rank_map['3'] = 2;
  rank_map['4'] = 3;
  rank_map['5'] = 4;
  rank_map['6'] = 5;
  rank_map['7'] = 6;
  rank_map['8'] = 7;
  rank_map['9'] = 8;
  rank_map['T'] = 9;
  rank_map['J'] = 10;
  rank_map['Q'] = 11;
  rank_map['K'] = 12;
}

void ReverseStack(stack<Card>& input) {
  stack<Card> tmp;
  while(!input.empty()) {
    tmp.push(input.top());
    input.pop();
  }
  input = tmp;
}


int main () {
  InitRankMap();
   
  string line;
  string four_lines;
  while (getline(cin, line)) {
    // read input
    if (line == "#") 
      break;
    four_lines = line;
    for (int i=0;i<3;++i) {
      getline(cin, line);
      four_lines = four_lines + " " + line;
    }
    // put four_lines into piles
    stringstream ss(four_lines);
    stack<Card> piles[13];
    string s_card;
    int index = 12;
    Card card;
    while (ss >> s_card) {
      card.rank = s_card[0];
      card.suit = s_card[1];
      piles[index].push(card);
      index = (index + 12) % 13;
    }
    for (int i=0;i<13;++i)
      ReverseStack(piles[i]);
    // simulation
    index = 12;
    int face_up = 0;
    while (!piles[index].empty()) {
      card = piles[index].top();
      //cout << "Pile: " << index << ", Card: " << card.rank << card.suit << endl;
      piles[index].pop();
      face_up++;
      index = rank_map[card.rank];
    }
    cout.width(2);
    cout.fill('0');
    cout << face_up;
    cout << "," << card.rank << card.suit << endl;
  }

}
