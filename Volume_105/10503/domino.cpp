#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
using namespace std;

bool solve(
        const vector<pair<int, int>>& dominos,
        map<int, set<int>>& graph,
        int n, int curr, int end,
        vector<bool>& used) {
    if (n == 0) {
        return curr == end;
    }

    for (int cand : graph[curr]) {
        if (!used[cand]) {
            used[cand] = true;
            auto domino = dominos[cand];
            int next (curr == domino.first ? domino.second : domino.first); 
            if (solve(dominos, graph, n-1, next, end, used)) {
                return true;
            }
            used[cand] = false;
        }
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n) {
        if (n == 0) break;
        cin >> m;
        // number -> indices
        map<int, set<int>> graph;
        vector<pair<int, int>> dominos;
        int a, b, S, T;
        cin >> a >> S;
        cin >> T >> b;
        for (int i=0;i<m;++i) {
            cin >> a >> b;
            dominos.push_back({a, b});
            if (graph.count(a) == 0) {
                graph[a] = set<int>();
            }
            graph[a].insert(i);
            if (graph.count(b) == 0) {
                graph[b] = set<int>();
            }
            graph[b].insert(i);
        }
        vector<bool> used(m, false);
        cout << (solve(dominos, graph, n, S, T, used) ? "YES" : "NO") << endl;
    }
}
