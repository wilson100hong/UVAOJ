#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define EMPTY_LINE -100

int getint() {
    string line;
    getline(cin, line);
    if (line == "") return EMPTY_LINE;
    stringstream ss(line);
    int x;
    ss >> x;
    return x;
}

string to_suit(int suit) {
    switch(suit) {
        case 0:
            return "Clubs";
        case 1:
            return "Diamonds";
        case 2:
            return "Hearts";
        case 3:
            return "Spades";
        defaut:
            return "Impossible";
    }
    return "X";
}

string to_value(int value) {
    switch(value) {
        case 9: 
            return "Jack";
        case 10:
            return "Queen";
        case 11:
            return "King";
        case 12:
            return "Ace";
        default:
            return to_string(value + 2);
    }
    return "X";
}

void print_card(int card) {
    int value = card % 13;
    int suit = card / 13;
    cout << to_value(value) << " of " << to_suit(suit) << endl;
}


vector<int> apply(const vector<int>& deck, const vector<int>& shuffle) {
    vector<int> ret(52, -1);
    for (int i=0;i<52;++i) {
        ret[i] = deck[shuffle[i]];
    }
    return ret;
}

int main() {
    string line;
    int T = getint();
    getint();  // blank line
    for (int t=0;t<T;++t) {
        int n = getint();
        int i=0;
        vector<vector<int>> shuffles(n, vector<int>(52, 0));
        while(i<n*52) {
            getline(cin, line);
            if (line == "") break;
            //cout << line << endl;
            stringstream ss(line);
            int x;
            while (ss >> x) {
                //cout << x << endl;
                shuffles[i/52][i%52] = x-1;
                ++i;
            }
        }
        //cout << "parsed" << endl;

        // initialize deck
        vector<int> deck;
        for (int i=0;i<52;++i) {
            deck.push_back(i);
        }   
        while (1) {
            int s = getint();
            if (s == EMPTY_LINE) break;
            // TODO: test
            s--;
            //cout << endl;

            deck = apply(deck, shuffles[s]);
            /*
            for (int y : deck) {
                cout << " " << y;
            }
            */
        }
        if (t > 0) cout << endl;
        for (const int card : deck) {
            print_card(card);
        }
    }
}
