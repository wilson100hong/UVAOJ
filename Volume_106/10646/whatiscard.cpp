#include <iostream> 
#include <vector>
#include <utility>
using namespace std;

int value(const string& card) {
    char c = card[0];
    if ('2' <= c && c <= '9') return c - '0';
    return 10;
}

void reverse(vector<string>& deck) {
    int l = 0, r = deck.size() - 1;
    while (l < r) {
        swap(deck[l], deck[r]);
        l++;
        r--;
    }
}

void dump(const vector<string>& deck) {
    /*
    for (auto card : deck) {
        cout << card << " ";
    }
    cout << endl;
    */
}

string solve(vector<string>& deck) {
    // Move top 25 cards 
    vector<string> hand(deck.begin(), deck.begin() + 25);
    deck.erase(deck.begin(), deck.begin() + 25);

    dump(hand);
    int Y = 0;
    for (int i=0;i<3;++i) {
        int X = value(deck[0]);
        dump(deck);
        //cout << X << endl;
        Y += X;
        deck.erase(deck.begin(), deck.begin() + 1 + 10 - X);
    }

    dump(deck);
    // put hands back
    deck.insert(deck.begin(), hand.begin(), hand.end());
    dump(deck);

    //cout << Y << endl;
    return deck[deck.size() - Y];
}


int main() {
    int T;
    cin >> T;
    for (int t=0;t<T;++t) {
        vector<string> deck;
        for (int i=0;i<52;++i) {
            string card;
            cin >> card;
            deck.push_back(card);
        }

        reverse(deck);
        dump(deck);
        cout << "Case " << t+1 << ": " << solve(deck) << endl;
    }
}

