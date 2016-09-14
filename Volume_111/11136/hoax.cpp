// Trap: bill can have same price
#include <iostream>
#include <map>
using namespace std;

int main() {
  int n, k;
  map<int, int> bills;
  while (1) {
    bills.clear();
    cin >> n;
    if (n == 0) break;
    unsigned long int paid = 0;
    while (n--) {
      cin >> k;
      while (k--) {
        int b;
        cin >> b;
        if (bills.count(b) == 0) {
          bills[b]= 0;
        }
        bills[b]++;
      }
      int min = bills.begin()->first;
      int max = bills.rbegin()->first;
      bills[min]--;
      if (bills[min] == 0) {
        bills.erase(min);
      }
      bills[max]--;
      if (bills[max] == 0) {
        bills.erase(max);
      }

      paid += (max - min);
    }
    cout << paid << endl;
  }
}

