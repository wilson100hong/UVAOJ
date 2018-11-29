#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int m, n;
    while (cin >> n >> m) {
        map<int, vector<int>> index;
        for (int i=0;i<n;++i) {
            int v;
            cin >> v;
            if (index.count(v) == 0) {
                index[v] = vector<int>();
            }
            index[v].push_back(i+1);
        }
        for (int i=0;i<m;++i) {
            int k, v;
            cin >> k >> v;
            if (index.count(v) > 0 && index[v].size() >= k) {
                cout << index[v][k-1]<< endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
}
