#include <iostream>
#include <vector>
#include <sstream>

//using namespace std;

struct Item{
  int p;  // price
  int f;  // favor
};

int solve(const std::vector<Item>& items, int m) {
  int a = m;
  if (m > 1800) {
    a += 200;
  }

  std::vector<Item> dp(a + 1, {0, 0});  // [0, m]
  int n = items.size();

  int best = 0;
  for (const auto& item : items) {
    std::vector<Item> copy = dp;
    for (int j=1;j<=a;++j) {
      Item alt = {0, 0};
      if (j >= item.p) {
        alt = {
            dp[j-item.p].p + item.p,
            dp[j-item.p].f + item.f
        };
      }
      if (alt.f > copy[j].f) {
        copy[j] = alt;
      }
      //std::cout << "copy[" << j << "]=" << copy[j].f << std::endl;;

      if (alt.f > best &&
          (j <= m || alt.p > 2000)) {
        best = alt.f;
      }
    }
    std::swap(dp, copy);
  }


  return best;
}

int main() {
  int m, n;
  std::string line;
  while (getline(std::cin, line)) {
    std::stringstream ss(line);
    ss >> m >> n;
    //std::cout << m << ", " << n << std::endl;

    std::vector<Item> items;
    items.reserve(n);

    for (int i=0;i<n;++i) {
      getline(std::cin, line);
      std::stringstream ss2(line);
      int p, f;
      ss2 >> p >> f;
      items.push_back({p, f});
    }


    //for (const auto& item : items) {
      //std::cout << item.p << ", " << item.f << std::endl;
    //}

    std::cout << solve(items, m) << std::endl;
  }
}
