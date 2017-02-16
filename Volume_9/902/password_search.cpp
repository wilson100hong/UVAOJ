// 2017/02/13
//
// Trap: 1) there could be multiple cases in one line
//       2) a case can be separated in multiple lines

#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;

int main() {
    int N;
    string text;
    unordered_map<string ,int> count;
    while (cin >> N) {
        cin >> text;
        count.clear();
        int best_cnt = 0;
        string best_ptn = "";
        int tz = text.size();
        for (int i=0; i+N <= tz; ++i) {
            string ptn = text.substr(i, N);
            count[ptn]++;
            if (count[ptn] > best_cnt) {
                best_cnt = count[ptn];
                best_ptn = ptn;
            }
        }
        cout << best_ptn << endl;
    }
}

