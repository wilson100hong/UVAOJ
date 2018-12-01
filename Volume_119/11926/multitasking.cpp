// 1. check start + period < end
// 2. use hash_map for insert start & end, then sort with map
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

int MAX_TIME = 1e6;

int main() {
    int n, m;
    while (cin >> n >> m) {
        bool passed = true;
        unordered_map<int, int> endpoints;
        if (n == 0 && m == 0) break;
        int start, end, period;
        for (int i=0;i<n;++i) {
            cin >> start >> end;
            endpoints[start]++;
            endpoints[end]--;
        }
        for (int i=0;i<m;++i) {
            cin >> start >> end >> period;
            if (start + period < end) {
                passed = false;
            }
            if (passed) {
                while (true) {
                    if (start >= MAX_TIME) break;
                    endpoints[start]++;
                    if (end >= MAX_TIME) break;
                    endpoints[end]--;
                    start += period;
                    end += period;
                }
            }
        }
        if (!passed) {
            cout << "CONFLICT" << endl;
            continue;
        }
        
        int tasks = 0;
        map<int, int> sorted;
        for (const auto& point : endpoints) {
            sorted[point.first] = point.second;
        }

        for (const auto& point : sorted) {
            // assume <x, -1> prior than <x, 1>
            tasks += point.second;
            if (tasks > 1) {
                passed = false;
                break;
            }
        }
        cout << (passed ? "NO CONFLICT" : "CONFLICT") << endl;
    }
}
