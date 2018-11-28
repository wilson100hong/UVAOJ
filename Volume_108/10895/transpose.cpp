#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main() {
    int M, N;
    while (cin >> M >> N) {
        vector<map<int, int>> trans(N, map<int, int>());
        for (int row=0;row<M;++row) {
            int n, col, val;
            cin >> n;
            vector<int> columns;
            for (int j=0;j<n;++j){ 
                cin >> col;
                col--;
                columns.push_back(col);
            }
            for (int j=0;j<n;++j){ 
                cin >> val;
                int col = columns[j];
                trans[col][row] = val;
            }
        }
        // dump
        cout << N << " " << M << endl;
        for (const auto& row : trans) {
            cout << row.size();
            for (const auto& col_val : row) {
                cout << " " << col_val.first + 1;
            }
            cout << endl;
            bool first = true;
            for (const auto& col_val : row) {
                if (first) {
                    first = false;
                } else { 
                    cout << " ";
                }
                cout << col_val.second;
            }
            cout << endl;
        }
    }
}

