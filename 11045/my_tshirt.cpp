#include <iostream>
#include <vector>

using namespace std;

int s2i(const string& s) {
  if (s == "XXL")
    return 0;
  if (s == "XL")
    return 1;
  if (s == "L")
    return 2;
  if (s == "M")
    return 3;
  if (s == "S")
    return 4;
  if (s == "XS")
    return 5;
  return -1;
}

bool augmented_path(
    const vector<vector<int> >& graph,
    vector<int>& match_person,
    vector<int>& match_shirt,
    vector<bool>& visit_shirt,
    int person) {
  for (const int& shirt : graph[person]) {
    if (!visit_shirt[shirt]) {
      visit_shirt[shirt] = true;
      if (match_shirt[shirt] == -1 ||
          augmented_path(graph, match_person, match_shirt, visit_shirt, match_shirt[shirt])) {
          match_person[person] = shirt;
          match_shirt[shirt] = person;
          return true;
       }
    }
  }
  return false;
}

int main() {
  int T;
  cin >> T;
  while (T--> 0) {
    int N, M;
    cin >> N >> M;
    vector<vector<int> > graph(M, vector<int>());  // person -> shirt 
    for (int m = 0; m < M; ++m) {
      for (int i = 0; i < 2; ++i) {
        string sz;
        cin >> sz;
        int shirt = s2i(sz);
        while (shirt < N) {
          graph[m].push_back(shirt);
          shirt += 6;
        }
      }
    }
    vector<int> match_shirt(N, -1);  // shirt -> person 
    vector<int> match_person(M, -1);  // person -> shirt 
    // Bipartie match
    int matches = 0;
    for (int m = 0; m < M; ++m) {
      if (match_person[m] == -1) {
        vector<bool> visit_shirt(N, false);
        if (augmented_path(graph, match_person, match_shirt, visit_shirt, m)) {
          matches++;
        }
      }
    }
    cout << (matches == M ? "YES" : "NO") << endl;
  }
}
