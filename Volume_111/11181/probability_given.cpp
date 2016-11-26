#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 2016/11/26
// STAR:
// SKILL:
// TRAP: 1) recursive function need to negate probabilities when remain == 0

double rec(const vector<double>& probs,
           vector<bool>& tried, 
           int index, int remain) {
    int n = probs.size();
    if (remain == 0) {
        double res = 1.0;
        // negate all rest non tried numbers
        for (int i=index;i<n;++i) {
            if (!tried[i]) {
                res *= (1-probs[i]);
            }
        }
        return res;
    }
    // remain > 0
    if (index >= n) return 0.0;  // impossible
    if (tried[index]) {
        return rec(probs, tried, index+1, remain);
    }
    tried[index] = true;
    double res = 0.0;
    // pick index
    res += probs[index]*rec(probs, tried, index+1, remain-1);
    // not pick index
    res += (1.0-probs[index])*rec(probs, tried, index+1, remain);
    tried[index] = false;
    return res;
}

vector<double> solve(const vector<double>& probs, int R) {
    int n = probs.size();
    vector<bool> tried(n, false);
    double denom = rec(probs, tried, 0, R);
    vector<double> cps;
    for (int i=0;i<probs.size();++i) {
        tried.assign(n, false);
        tried[i] = true;
        double cp = probs[i]*rec(probs, tried, 0, R-1);
        cp /= denom;
        cps.push_back(cp);
    }
    return cps;
}

// TODO: use double first, if precision error, use int
int main() {
    int N, R;
    int cases = 1;
    while (cin >> N >> R) {
        if (N==0 && R==0) break;
        cout << "Case " << cases++ << ":" << endl;
        vector<double> probs;
        for (int i=0;i<N;++i) {
            double p;
            cin >> p;
            probs.push_back(p);
        }
        vector<double> cps = solve(probs, R);
        for (double cp : cps) {
            cout << fixed;
            cout << setprecision(6) << cp << endl;
        }
    }
}
