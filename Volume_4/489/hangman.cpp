#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int T;
    while (cin >> T) {
        if (T == -1) break;
        cout << "Round " << T << endl;
        string answer, guess;
        cin >> answer;
        cin >> guess;
        set<char> letters;
        for (char c : answer) {
            letters.insert(c);
        }
        set<char> tries;
        int wrong = 0;
        for (char c : guess) {
            // Ignore duplicate letters (no matter success or not)
            if (tries.count(c) != 0) continue;
            if (letters.count(c) != 0) {
                letters.erase(c);
                if (letters.empty()) break;
            } else {
                wrong++;
                if (wrong == 7) break;
            }
            tries.insert(c);
        }
        if (wrong == 7) {
            cout << "You lose." << endl;
        } else if (letters.empty()) {
            cout << "You win." << endl;
        } else {
            cout << "You chickened out." << endl;
        }
    }

}
