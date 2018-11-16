#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void f(vector<int>& g) {
    vector<int> tmp(9, 0);
    for (int r=0;r<3;++r) {
        for (int c=0;c<3;++c) {
            int sum = 0;
            for (int d=0;d<4;++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (0<= nr && nr < 3 && 0<= nc && nc < 3) { 
                    sum += g[nr*3 + nc];
                }
            }
            tmp[r*3+c] = sum % 2;
        }
    }
    g = tmp;
}

void dump(const vector<int>& g) {
    for (int i=0;i<3;++i) {
        for (int j=0;j<3;++j) {
            cout << g[i*3+j];
        }
        cout << endl;
    }
}

int encode(const vector<int>& g) {
    int e = 0;
    for (int i=0;i<9;++i) {
        e += (g[i] << i);
    }
    return e;
}

int solve(vector<int>& g) {
    vector<int> steps(1<<9, -1);
    int step = 0;
    steps[encode(g)] = 0;
    while (true) {
        f(g);
        int e = encode(g);
        if (steps[e] != -1) {
            return steps[e] - 1;
        } else {
            steps[e] = ++step;
        }
    }
}


int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int T;
    ss >> T;
    while (T--) {
        getline(cin, line);  // empty line
        vector<int> g(9, 0);
        for (int i=0;i<3;++i) {
            getline(cin, line);
            for (int j=0;j<3;++j) {
                g[i*3 + j] = line[j] - '0';
            }
        }
        cout << solve(g) << endl;
    }
}
