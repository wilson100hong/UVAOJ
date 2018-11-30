#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

int main() {
    int N, M;
    char c;
    while (cin >> N) {
        map<char, set<char>> graph;
        cin >> M;
        set<char> curr;
        set<char> wake;
        map<char, int> stimulate;
        for (int i=0;i<3;++i) {
            cin >> c;
            curr.insert(c);
            wake.insert(c);
        }
        for (int i=0;i<M;++i) {
            char a, b;
            cin >> a >> b;
            if (graph.count(a) == 0) {
                graph[a] = set<char>();
                stimulate[a] = 0;
            }
            if (graph.count(b) == 0) {
                graph[b] = set<char>();
                stimulate[b] = 0;
            }
            graph[a].insert(b);
            graph[b].insert(a);
        }

        int years = 0;
        while(!curr.empty() && wake.size() < N) {
            set<char> next;
            for (char a : curr) {
                for (char b : graph[a]) {
                    if (!wake.count(b) && !next.count(b)) {
                        stimulate[b]++;
                        if (stimulate[b] >= 3) {
                            next.insert(b);
                            wake.insert(b);
                        }
                    }
                }
            }
            curr = next;
            years++;
        }
        if (wake.size() == N) {
            cout << "WAKE UP IN, " << years << ", YEARS" << endl;
        } else {
            cout << "THIS BRAIN NEVER WAKES UP" << endl;
        }
    }
}
