// NOTE: use min-heap. In priority_queue, the comparator is greator<>
#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

using namespace std;

struct Signal {
    long id;
    long ts;  // timestamp
    long period;

    bool operator< (const Signal& o) const {
        if (ts != o.ts) {
            return ts > o.ts;
        }
        return id > o.id;
    }
};

typedef priority_queue<Signal> SignalQueue;

// REDU
int main() {
    SignalQueue sq;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "#") break;
        stringstream ss(line);
        string dummy;
        ss >> dummy;  // "Register"
        long id, period;
        ss >> id >> period;
        sq.push({id, period, period});
    }
    getline(cin, line);
    stringstream ss2(line);
    int k;
    ss2 >> k;
    while (k--) {
        Signal sig = sq.top();
        cout << sig.id << endl;
        sq.pop();
        sq.push({sig.id, sig.ts + sig.period, sig.period}); 
    }
}

