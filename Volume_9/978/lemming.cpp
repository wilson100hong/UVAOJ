// NOTE: set is sort from small to large.
// NOTE: set will deduplicate.
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

typedef priority_queue<int> pq;

void solve(int B, pq& green, pq& blue) {
    vector<int> battles;
    while (!green.empty() && !blue.empty()) {
        // TODO
        // 1. pick highest B lemmings from both group
        for (int i=0;i<B;++i) {
            if (green.empty() && blue.empty()) break;
            int g = 0, b = 0;
            if (!green.empty()) {
                g = green.top();
                green.pop();
            }
            if (!blue.empty()) {
                b = blue.top();
                blue.pop();
            }
            battles.push_back(g - b);
        }

        for (int battle : battles) {
            if (battle > 0) {
                green.push(battle);
            } else if (battle < 0) {
                blue.push(-battle);
            }
        }
        battles.clear();
    }

    if (green.empty() && blue.empty()) {
        cout << "green and blue died" << endl;
    } else if (green.empty()) {
        cout << "blue wins" << endl;
        while (!blue.empty()) {
            cout << blue.top() << endl;
            blue.pop();
        }
    } else {
        cout << "green wins" << endl;
        while (!green.empty()) {
            cout << green.top() << endl;
            green.pop();
        }
    }
}

int main() {
    int T;
    cin >> T;
    bool first = true;
    while (T--) {
        int B, SG, SB, x;
        cin >> B >> SG >> SB;
        pq green;
        pq blue;
        while (SG--) {
            cin >> x;
            green.push(x);
        }
        while (SB--) {
            cin >> x;
            blue.push(x);
        }

        if (!first) {
            cout << endl;
        } else {
            first = false;
        }
        solve(B, green, blue);
    }
}
