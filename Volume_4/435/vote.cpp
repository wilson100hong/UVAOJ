#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


int rec_power(int sum, int index, int cnd, const vector<int>& number, vector<bool>& party) { 
  int n = number.size();
  if (index == n) {
    int vote = 0;
    for (int i = 0; i < n; ++i) {
      if (i == cnd || party[i])
        vote += number[i];
    }
    if ((vote*2 > sum) && ((vote-number[cnd])*2 <= sum))
      return 1;
    else 
      return 0;
  }
  // skip candidate
  if (index == cnd)
    return rec_power(sum, index + 1, cnd, number, party);

  party[index] = true;
  int result = rec_power(sum, index + 1, cnd, number, party);
  party[index] = false;
  result += rec_power(sum, index + 1, cnd, number, party);
  return result;
}

vector<int> solve(const vector<int>& number) {
  int sum = 0;
  for (int i = 0; i < number.size(); ++i) 
    sum += number[i];
  
  vector<bool> party(number.size(), false);
  vector<int> power;
  for (int i = 0; i < number.size(); ++i) {
    for (int i = 0; i < party.size(); ++i)  // init party
      party[i] = false;
    power.push_back(rec_power(sum, 0, i, number, party));
  }
  return power;
}

int main() {
  int round;
  cin >> round;
  while (round-- > 0) {
    int n;
    cin >> n;
    vector<int> number;
    for (int i = 0; i < n; ++i) {
      int num;
      cin >> num;
      number.push_back(num);
    }
    vector<int> ans = solve(number);
    for (int i = 0; i < ans.size(); ++i)
      cout << "party " << i + 1 << " has power index " << ans[i] << endl;
    cout << endl;
  }
}
