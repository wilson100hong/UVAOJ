#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;
        unordered_map<int, int> snakes;
        for (int i=0;i<b;++i) {
            int x, y;
            cin >> x >> y;
            snakes[x] = y;
        }

        vector<int> players(a, 1);
        bool end = false;
        for (int i=0;i<c;++i) {
            int dice;
            cin >> dice;

            if (!end && a > 0) {
                int p = i % a;
                int& player = players[p];
                player += dice;
                if (snakes.count(player) != 0) {
                    player = snakes[player];
                }
                if (player >= 100) {
                    player = 100;
                    end = true;
                }
            }
        }
    
        for (int i=0;i<a;++i) {
            cout << "Position of player " << i+1 << " is " << players[i] << "." << endl;
        }

    }
}
