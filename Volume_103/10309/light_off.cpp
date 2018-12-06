#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
typedef unsigned long UL;
int min(int a, int b) {
    return a < b ? a : b;
}

void dump_mask(UL mask) {
    vector<bool> actions(10, false);
    for (int i=9;i>=0;--i) {
        actions[i] = mask & 1;
        mask = mask >> 1;
    }
    for (bool a : actions) {
        cout << (a ? "1" : "0");
    }
    cout << endl;
}

void dump(const vector<vector<bool>>& lights) {
    for (int i=0;i<10;++i) {
        for (int j=0;j<10;++j) {
            cout << (lights[i][j] ? 'O' : '#');
        }
        cout << endl;
    }
}
vector<bool> get_actions(UL mask) {
    vector<bool> actions(10, false);
    for (int i=9;i>=0;--i) {
        actions[i] = mask & 1;
        mask = mask >> 1;
    }
    return actions;
}

int IMPSSOIBLE = 1000;
int di[] = {0, 0, 0, 1};
int dj[] = {-1, 0, 1, 0};
int simulate(vector<vector<bool>>& lights, vector<bool>& actions) {
    int steps = 0;
    for (int i=0;i<10;++i) {
        // 1.apply actions
        for (int j=0;j<10;++j) {
            if (actions[j]) {
                steps++;
                // switch!
                for (int k=0;k<4;++k) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (ni >= 0 && ni < 10 && nj >= 0 && nj < 10) {
                        lights[ni][nj] = !lights[ni][nj];
                    }
                }
                // specify next actions
            }
        }
        for (int j=0;j<10;++j) {
            actions[j] = lights[i][j];
        }
    }
    
    // Checks the last row
    for (int j=0;j<10;++j) {
        if (lights[9][j]) {
            return IMPSSOIBLE;
        }
    }
    return steps;
}
int solve(const vector<vector<bool>>& input) {
    // 2^10 combinations for first row
    // 1-> switch 0-> no-op
    int best = IMPSSOIBLE;
    vector<bool> actions(10, false);

    for (UL mask = 0; mask < (1<<10); ++mask) {
        vector<vector<bool>> lights = input;
        vector<bool> actions = get_actions(mask);
        int steps = simulate(lights, actions);
        best = min(best, steps);
    }
    return best > 100 ? -1 : best;
}

int main() {
    string line;
    vector<vector<bool>> lights(10, vector<bool>(10, false));
    while (getline(cin, line)) {
        if (line == "end") break;
        cout << line << " ";
        for (int i=0;i<10;++i) {
            getline(cin, line);
            for (int j=0;j<10;++j) {
                char c = line[j];
                lights[i][j] = (c == '#' ? false : true);
            }
        }
        cout << solve(lights) << endl;
    }
}
