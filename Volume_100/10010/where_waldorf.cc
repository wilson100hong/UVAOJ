#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

stringstream& eatline(stringstream& ss) {
  string line;
  getline(cin, line);
  ss.clear();
  ss.str(line);
  return ss;
}

string to_lower(const string& s) {
  string r = s;
  for (int i=0;i<r.size();++i) {
    if (r[i] >= 'A' && r[i] < 'a') {
      r[i] = r[i] - 'A' + 'a';
    }
  }
  return r;
}

// directions, from 12'o clock (upward), clock-wise
int di[] = {-1,-1, 0, 1, 1, 1, 0, -1};
int dj[] = { 0, 1, 1, 1, 0,-1,-1, -1};

void solve(const vector<string>& grid, const string& query) {
  int M = grid.size(), N = grid[0].size();
  int q_len = query.size();

  for (int i=0;i<M;++i) {
    for (int j=0;j<N;++j) {
      for (int dir=0;dir<8;dir++) {
        int xi = i + di[dir]*(q_len-1), xj = j + dj[dir]*(q_len-1);
        // out of bound
        if (xi < 0 || xi >= M || xj < 0 || xj >= N) continue;
        bool match = true;
        for (int k=0;k<q_len;++k) {
          int ki = i + di[dir]*k, kj = j + dj[dir]*k;
          // mismatch
          if (grid[ki][kj] != query[k]) {
            match = false;
            break;
          }
        }
        if (match) {
          cout << i+1 << " " << j+1 << endl;
          return;
        }
      }
    }
  }
  cout << "NOT FOUND " << query << endl;
}

int main() {
  stringstream ss;

  int T;
  eatline(ss) >> T;
  
  bool first = true;
  while (T--) {
    eatline(ss);  // blanline between cases
    int M, N;
    eatline(ss) >> M >> N;
    vector<string> grid;
    for (int row=0;row<M;++row) {
      string line;
      eatline(ss) >> line;
      grid.push_back(to_lower(line));
    }

    int Q;
    eatline(ss) >> Q;
    if (!first) cout << endl;
    first = false;
    while (Q--) {
      string query;
      eatline(ss) >> query;
      solve(grid, to_lower(query));
    }
    
  }
  

}
