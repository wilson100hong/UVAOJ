#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        queue<int> q;
        stack<int> st;
        priority_queue<int> pq;
        bool is_q, is_st, is_pq;
        is_q = is_st = is_pq = true;
        for (int i=0;i<n;++i) {
            int op, x;
            cin >> op >> x;
            if (op == 1) {
                q.push(x);
                st.push(x);
                pq.push(x);
            } else if (op == 2) {
                if (is_q) {
                    if (q.empty()) {
                        is_q = false;
                    } else {
                        is_q &= (q.front() == x);
                        q.pop();
                    }
                }
                if (is_st) {
                    if (st.empty()) {
                        is_st = false;
                    } else {
                        is_st &= (st.top() == x);
                        st.pop();
                    }
                }
                if (is_pq) {
                    if (pq.empty()) {
                        is_pq = false;
                    } else {
                        is_pq &= (pq.top() == x);
                        pq.pop();
                    }
                }
            }
        }
        int total = static_cast<int>(is_q) + static_cast<int>(is_st) + static_cast<int>(is_pq);
        if (total == 0) {
            cout << "impossible" << endl;
        } else if (total > 1) {
            cout << "not sure" << endl;
        } else {
            if (is_q) {
                cout << "queue" << endl;
            } else if (is_st) {
                cout << "stack" << endl;
            } else {
                cout << "priority queue" << endl;
            }
        }



    }
}
