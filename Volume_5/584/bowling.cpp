#include <iostream>
#include <sstream>
using namespace std;

int solve(const string& line) { 
    stringstream ss(line);
    char c;
    int total = 0;
    int round2 = 0;  // round * 2
    // prev, prev*2;
    int cur_bonus = 0, next_bonus = 0;
    int last = -1;
    while (ss >> c) {
        int pins;
        if (c == 'X') {
            pins = 10;
            round2 += 2; 
        } else if (c == '/') {
            pins = 10 - last;
            round2 += 1; 
        } else {
            pins = c - '0';
            round2 += 1; 
        }
            
        /*
        cout << "c: " << c << endl;
        cout << "pins: " << pins << endl;
        cout << "total: " << total << endl;
        */

        total += pins * (1 + cur_bonus);
        // advance
        cur_bonus = next_bonus;
        next_bonus = 0;

        if (round2 < 20) {
            if (c == 'X') {
                cur_bonus += 1;
                next_bonus += 1;
            } else if (c == '/' ) {
                cur_bonus += 1;
            }
        }
        last = pins;
    }

    return total;
}

int main() {
    string line;
    while (true) {
        getline(cin, line);
        if (line == "Game Over") break;
        cout << solve(line) << endl;
    }
}
