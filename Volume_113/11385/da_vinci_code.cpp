#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
using namespace std;

typedef unsigned long int UL;

// 0-based index
unordered_map<UL, int> INDICE;

void init() {
    // build INDICE
    int index = 0;
    UL first = 1, second = 2;
    INDICE[first] = index++;
    INDICE[second] = index++;
    while (second <= (1<<30)) {
        UL third = first + second;
        INDICE[third] = index++;
        first = second;
        second = third;
    }
}

stringstream SS;
stringstream& eatline() {
    SS.clear();
    string line;
    getline(cin, line);
    SS.str(line);
    return SS;
}

int main() {
    init();
    int T;
    eatline() >> T;
    while (T--) {
        int N;
        eatline() >> N;
        stringstream& ss = eatline();
        vector<UL> ordering;
        int len = 0;
        while (N--) {
            UL number;
            ss >> number;
            int index = INDICE[number]; 
            if (index + 1 > len) len = index+1;
            ordering.push_back(index);
        }
        string output(len, ' ');

        string text;
        getline(cin, text);
        int i = 0;
        for (char c : text) {
            if ('A' <= c && c <= 'Z') {
                output[ordering[i]] = c;
                i++;
                if (i == ordering.size()) break;
            }
        }
        cout << output << endl;
    }
}
