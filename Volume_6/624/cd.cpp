#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}

int rec_solve(const vector<int>& tracks, int tape,
    int index, long int sum, vector<bool>& used,
    vector<bool>* choice) {
  long int ans = sum;
  *choice = used;
  
  for (int i = index; i < tracks.size(); ++i) {
    if (sum + tracks[i] <= tape) {
      used[i] = true;
      vector<bool> rec_choice;
      long int tmp = rec_solve(tracks, tape, i + 1, sum + tracks[i], used, &rec_choice);
      if (tmp > ans) {
        ans = tmp;
        *choice = rec_choice;
      }
      used[i] = false;
    }
  }
 
  return ans;
}

void solve(const vector<int>& tracks, int tape) {
  vector<bool> choice;
  vector<bool> used(tracks.size(), false);
  int ans = rec_solve(tracks, tape, 0, 0, used, &choice);

  for (int i = 0; i < choice.size(); ++i) {
    if (choice[i]) {
      cout << tracks[i] << " ";
    }
  }
  cout << "sum:" << ans << endl;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    int T, N;
    ss >> N >> T;
    vector<int> tracks;
    for (int t = 0; t < T; ++t) {
      int len;
      ss >> len;
      tracks.push_back(len);
    }
    solve(tracks, N);
  }
}
