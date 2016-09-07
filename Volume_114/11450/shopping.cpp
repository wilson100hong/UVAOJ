#include <iostream>
#include <vector>
#include <set>
using namespace std;

int max(int a, int b) {
  return a >= b ? a : b;
}

void solve(int money, const vector<set<int>>& items) {
  // test possible
  int sum = 0;
  for (const set<int>& garment : items) {
    sum += *garment.begin();
  }
  if (sum > money) {
    cout << "no solution" << endl;
    return;
  }

  //vector<vector<int>> dp(items.size(), vector<int>(money+1, -1));
  vector<int> dp(money+1, -1);
  // first row
  for (int j = 0; j <= money; ++j) {
    for (int price : items[0]) {
      if (j >= price)
        dp[j] = price;
    }
  }


  // TODO: can use 1-D array
  for (int i = 1; i < items.size(); ++i) {
    vector<int> temp(money+1, -1);
    for (int j = 0; j <= money; ++j) {
      for (int price : items[i]) {
        if (j < price)
          // not enough money for the price
          continue;
        if (dp[j-price] == -1) 
          // not even satisfy for class 0 ~ i-1
          continue;
        // compare this buy worths or not
        temp[j] = max(temp[j], dp[j-price] + price);
      }
    }
    dp = temp;
  }

  cout << dp[money] << endl;
}

int main() {
  int rounds;
  cin >> rounds;
  while (rounds--) {
    int M, C; 
    cin >> M >> C;
    vector<set<int>> items;
    for (int c = 0; c < C; ++c) {
      int K;
      cin >> K;
      set<int> garment;
      for (int k = 0; k < K; ++k) {
        int price;
        cin >> price;
        garment.insert(price);
      }
      items.push_back(garment);
    }
    solve(M, items);
  }
}
