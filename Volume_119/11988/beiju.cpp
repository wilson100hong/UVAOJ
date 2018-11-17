// 1. TLE: minimize string prepend.
#include <iostream>
#include <list>
using namespace std;

void solve(const string& line) {
    list<string> output;
    output.push_back("");
    bool prepend = false;
    string head = "";
    for (char c : line) {
        if (c == '[' || c == ']') {
            if (head != "") {
                output.push_front(head);
                head = "";
            }
            prepend = (c == '[');
        } else {
            if (!prepend) {
                output.back().push_back(c);
            } else {
                head.push_back(c);
            }
        }
    }

    if (head != "") {
        output.push_front(head);
        head = "";
    }
    for (const string& s : output) {
        cout << s;
    }
    cout << endl;
}

int main() {
    string line;
    while (getline(cin, line)) {
        solve(line);
    }
}
