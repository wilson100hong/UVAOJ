// NOTE: carrier can unload at destination even queue is full.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int solve(vector<queue<int>>& stations, int S, int Q) {
    int N = stations.size();
    stack<int> carrier;
    int time = 0;
    int pos = 0;
    while (true) {
        queue<int>& station = stations[pos];

        // 1. offload
        while (!carrier.empty()) {
            int item = carrier.top(); 
            if (item == pos) {
                carrier.pop();
            } else if (station.size() < Q) {
                carrier.pop();
                station.push(item);
            } else {
                break;
            }
            time++;
        }

        // 2. upload
        while (!station.empty() && carrier.size() < S) {
            int item = station.front(); 
            time++;
            station.pop();
            carrier.push(item);
        }

        bool done = carrier.empty();
        if (done) {
            for (const auto& st : stations) {
                if (!st.empty()) {
                    done = false;
                }
            }
        }
        if (done) {
            break;
        }

        // move to next station
        time += 2;
        pos = (pos+1) % N;
    }

    return time;
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, S, Q;
        cin >> N >> S >> Q;
        vector<queue<int>> stations(N, queue<int>());
        for (int i=0;i<N;++i) {
            int n;
            cin >> n;
            while (n--) {
                int x;
                cin >> x;
                stations[i].push(x-1);
            }
        }
        cout << solve(stations, S, Q) << endl;
    }
}
