#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int solve(const vector<vector<char>>& image, int R, int C, int M, int N) {
    unordered_map<char, int> counts;
    int max = 0;
    for (int i=0;i<R;++i) {
        for (int j=0;j<C;++j) {
            char c = image[i][j];
            if (counts.count(c) == 0) {
                counts[c] = 0;
            }
            counts[c]++;
            if (counts[c] > max) {
                max = counts[c];
            }
        }
    }
    int total = 0;
    for (const auto& kv : counts) {
        if (kv.second == max) {
            total += kv.second * M;
        } else {
            total += kv.second * N;
        }
    }
    return total;
}

int main() {
    int X;
    cin >> X;
    for (int x=1;x<=X;++x) {
        int R, C, M, N;
        cin >> R >> C >> M >> N;
        vector<vector<char>> image(R, vector<char>(C, 0));
        for (int i=0;i<R;++i) {
            for (int j=0;j<C;++j) {
                char c;
                cin >> c;
                image[i][j] = c;
            }
        }
        cout << "Case " << x << ": " << solve(image, R, C, M, N) << endl;
    }
}
