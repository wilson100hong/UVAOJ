#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int round;
    cin >> round;

    while (round--) {
        int a, b;
        cin >> a >> b;

        if (a > b) {
            cout << ">" << endl;
        } else if (a < b) {
            cout << "<" << endl;
        } else {
            cout << "=" << endl;
        }
    }
    return 0;
}
