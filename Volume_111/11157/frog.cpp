#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;
typedef long long LL;

struct Stone {
    bool small;  // true for small 
    LL m;
};

bool satisfy(int D, const vector<Stone>& stones, int M) {
    // from left to right
    vector<bool> used(stones.size(), false);
    LL pos = 0;
    int index = 0;  // next stone to try
    while (pos + M < D) {
        bool move = false;
        // jump to closest biggest stone
        while (index < stones.size() && stones[index].m - pos <= M) {
            if (!stones[index].small) {
                // big stone
                pos = stones[index].m;
                move = true;
                index++;
                break;
            }
            index++;
        }
        if (!move) {
            // use farest small stone
            if (index > 0 && stones[index-1].m > pos) {
                pos = stones[index-1].m;
                used[index-1] = true;
                move = true;
            }
        }
        if (!move) return false;
    }
    // from right to left
    pos = D;
    index = stones.size() - 1;
    while (pos > M) {
        // find any next stones can use
        while (index >= 0 && used[index]) {
            index--;
        }
        if (index < 0 || (pos-stones[index].m > M)) return false;
        pos = stones[index].m;
        index--;
    }
    return true;
}

int solve(LL D, const vector<Stone>& stones) {
    LL L = 1, R = D;
    while (R > L) {
        LL M = (L + R) / 2;
        if (satisfy(D, stones, M)) {
            R = M;
        } else {
            L = M + 1; 
        }
    }
    return R;
}

int main() {
    int T;
    cin >> T;
    for (int t=0;t<T;++t) {
        int N;
        LL D;
        cin >> N >> D;

        vector<Stone> stones;
        for (int i=0;i<N;++i) {
            string line;
            cin >> line;
            char c;
            LL M;
            sscanf(line.c_str(), "%c-%lld", &c, &M);
            bool small = (c == 'S');
            Stone stone = {small, M};
            stones.push_back(stone);
        }
        cout << "Case " << t+1 << ": ";
        cout << solve(D, stones) << endl;
    }

}

