#include <iostream>
using namespace std;

int main() {
    string line;
    int T = 1;
    while (getline(cin, line)) {
        if (line == "*") break;
        cout << "Case " << T++ << ": ";
        if (line == "Hajj") cout << "Hajj-e-Akbar";
        if (line == "Umrah") cout << "Hajj-e-Asghar";
        cout << endl;
    }
}
