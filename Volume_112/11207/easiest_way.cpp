#include <iostream>
using namespace std;

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double birdSize(double w, double h) {
    double maxSize = 0.0;
    // try 1*4 
    maxSize = max(maxSize, min(h, w/4.0));
    
    // try 2*2
    maxSize = max(maxSize, min(h/2.0, w/2.0));
    
    // try 4*1
    maxSize = max(maxSize, min(h/4.0, w));
    return maxSize;
}

int main() {
    int N, w, h;
    while (cin >> N) {
        if (!N) break;
        double maxSize = 0.0, maxIndex = -1;

        for (int i=1;i<=N;++i) {
            cin >> w >> h;
            double bs = birdSize(w, h);
            if (bs > maxSize) {
                maxSize = bs;
                maxIndex = i;
            }
        }
        cout << maxIndex << endl;
    }

}
