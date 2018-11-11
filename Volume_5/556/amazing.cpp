#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;

// direction
// 0:right, 1:down, 2:left, 3:up

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

void solve(const vector<vector<bool>>& maze, int h, int w) {
    vector<vector<int>> counts(h, vector<int>(w, 0));
    int r = h-1, c = 0;
    int dir = 0;

    do {
        // decide direction
        for (int d=1;d>=-2;--d) {
            int new_dir = (dir + d + 4) % 4;
            int nr = r + dr[new_dir];
            int nc = c + dc[new_dir];
            if (0 <= nr && nr < h  && 0 <= nc && nc < w && !maze[nr][nc]) {
                // move toward direction
                dir = new_dir;
                r = nr;
                c = nc;
                break;
            }
        }
        // increase count
        counts[r][c]++;
    } while (!(r==h-1 && c==0));



   vector<int> freq(5, 0);
    for (int r=0;r<h;++r) {
        for (int c=0;c<w;++c) {
            if (!maze[r][c]) {
                freq[counts[r][c]]++;
            }
        }
    }


    for (int f : freq) {
        cout << setw(3);
        cout << f;
    }
    cout << endl;
}

int main() {
    int h, w;
    while (cin >> h >> w) {
        if (h==0 && w==0) break;
        vector<vector<bool>> maze(h, vector<bool>(w, false));
        for (int r=0;r<h;++r) {
            for (int c=0;c<w;++c) {
                char x;
                cin >> x;
                maze[r][c] = x - '0';
            }
        }
        solve(maze, h, w);
    }
}
