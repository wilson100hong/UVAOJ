#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

double solve(int cows, int cars, int shows) {
  double sum = cows + cars;
  //return static_cast<double>(cows / sum) * static_cast<double>(cars / (sum - shows - 1)) +
         //static_cast<double>(cars / sum) * static_cast<double>((cars - 1) / (sum - shows - 1)); 
  return (cows / sum) * (cars / (sum - shows - 1)) +
         (cars / sum) * ((cars - 1) / (sum - shows - 1)); 
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    int cows, cars, shows;
    ss >> cows >> cars >> shows;
    cout << fixed;
    cout << setprecision(5);
    cout << solve(cows, cars, shows) << endl;
  }
}
