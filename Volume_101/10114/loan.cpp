#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
struct Dep{
  int month;
  long double rate;
};
int main() {
  string line;
  while(getline(cin, line)) {
    stringstream ss(line);
    // input format: 30 500.0 15000.0 3
    int months, n;
    long double down, loan;
    ss >> months >> down >> loan >> n;
    if (months < 0) {
      break;
    }
    long double value = down + loan;
    long double mpay = loan / months;
    vector<Dep> deps;
    while (n-- > 0) {
      getline(cin, line);
      stringstream ss2(line);
      Dep dep;
      ss2 >> dep.month >> dep.rate;
      deps.push_back(dep);
    }

    //if (deps.size() == 0 || deps[0].month != 0) {
      //cout << "WRONG INPUT" << endl;
      //continue;
    //}
    int ans = 0, index = 0;
    while (1) {
      // TODO: calculate value
      if (index + 1 < deps.size() && deps[index + 1].month <= ans) {
        index++;
      }
      if (deps.size() != 0) {
        value *= (1.0F - deps[index].rate); 
      }
      if (loan < value) {
        //cout << "loan: " << loan << endl;
        //cout << "value: " << value << endl;
        break;
      }
      ans++;
      loan -= mpay;
    }
    cout << ans << " month" << (ans == 1 ? "" : "s") << endl;
  }
}
