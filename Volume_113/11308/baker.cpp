#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <set>
using namespace std;

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

string upper(const string& s) {
  string result = s;
  for (int i=0; i<result.size(); ++i) {
    char c = result[i];
    if ('a' <= c && c <= 'z') {
      c = c - 'a' + 'A';
      result[i] = c;
    }
  }
  return result;
}

bool is_digit(char c) {
  return '0'<=c && c<='9';
}

int s2i(const string& s) {
  int result = 0;
  for (int i=0;i<s.size();++i) {
    int digit = s[i]-'0';
    result = result*10 + digit;
  }
  return result;
}

pair<string, int> parse_ingredient_number(const string& line) {
  int cur = line.size()-1;
  while(cur >= 0) {
    if (!is_digit(line[cur])) {
      break;
    }
    cur--;
  }
  // we assume line[cur] is space!
  string ing = line.substr(0, cur);
  string ps = line.substr(cur+1);
  int price = s2i(ps);
  return {ing, price};
}

int main() {
  int cases;
  eatline() >> cases;
  while (cases--) {
    string store_name;
    getline(cin, store_name);
    cout << upper(store_name) << endl;
    int M, N, B;
    eatline() >> M >> N >> B;
    map<string, int> prices;
    for (int m=0;m<M;++m) {
      string line;
      getline(cin, line); 
      string ing;
      int price;
      tie(ing, price) = parse_ingredient_number(line);
      prices[ing] = price;
    }

    set<pair<int, string>> available;
    for (int n=0;n<N;++n) {
      string recipe;
      getline(cin, recipe);
      int K;
      eatline() >> K;
      int cost = 0;
      for (int k=0;k<K;++k) {
        string line;
        getline(cin, line); 
        string ing;
        int count;
        tie(ing, count) = parse_ingredient_number(line);
        cost += (prices[ing] * count);
      }
      if (cost <= B) {
        available.insert({cost, recipe});
      }
    }
    
    if (available.empty()) {
      cout << "Too expensive!" << endl;
    } else {
      for (const auto& kv : available) {
        cout << kv.second << endl;
      }
    }
    cout << endl;
  }
}

