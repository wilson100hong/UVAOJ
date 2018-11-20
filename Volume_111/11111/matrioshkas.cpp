#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

struct Doll {
    int cap;
    int size; 
};

string solve(const string& line) {
    stack<Doll> st;
    
    stringstream ss(line);
    int x;
    bool ok = true;
    while (ss >> x) {
        if (x < 0) {
            int size = -x;
            if (!st.empty()) {
                Doll& doll = st.top();
                doll.size += size;
                if (doll.size >= doll.cap) {
                    ok = false;
                    break;
                }
            }
            st.push({size, 0});
        } else {  // x > 0
            if (st.empty()) {
                ok = false;
                break;
            }
            Doll& doll = st.top();
            if (doll.cap != x) {
                ok = false;
                break;
            }
            st.pop();
        }
    }

    ok &= st.empty();
    
    return ok ? ":-) Matrioshka!" : ":-( Try again.";
}

int main() {
    string line;
    while (getline(cin, line)) {
        cout << solve(line) << endl;    
    }
}
