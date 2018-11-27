#include <iostream>
#include <map>
#include <sstream>
#include <cctype>
#include <cstdlib>
using namespace std;


int s2i(const string& f) {
    int res = 0;
    for (char c : f) {
        if (isdigit(c)) {
            res = res*10 + (c-'0');
        }
    }
    return res;
}

stringstream& eatline(stringstream& ss) {
    string line;
    getline(cin, line);
    ss.clear();
    ss.str(line);
    return ss;
}

int main() {
    stringstream ss;
    int P, G;
    eatline(ss) >> P >> G;
    map<string, int> parties;
    
    for (int i=0;i<P;++i) {
        string name, f;
        eatline(ss) >> name >> f;
        parties[name] = s2i(f);
    }
    /*
    for (const auto& kv : parties) {
        cout << kv.first << ": " << kv.second << endl;
    }
    */
    for (int i=0;i<G;++i) {
        cout << "Guess #" << i+1 << " was ";
        eatline(ss);
        string token;
        int total = 0;
        while (ss >> token) {
            if (parties.count(token) != 0) {
                total += parties[token];
            } else if (token != "+") {
                break;
            }
        }
        string op = token;
        int expected;
        ss >> expected;
        expected *= 10;
        /*
        cout << total << endl;
        cout << expected << endl;
        */
        bool passed = true;
        if (op == "<") {
            passed = (total < expected);
        } else if (op == ">") {
            passed = (total > expected);
        } else if (op == "<=") {
            passed = (total <= expected);
        } else if (op == ">=") {
            passed = (total >= expected);
        } else if (op == "=") {
            passed = (total == expected);
        }
        if (!passed) cout << "in";
        cout << "correct." << endl;
    }
}
