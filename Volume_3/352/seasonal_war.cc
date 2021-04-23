#include <iostream>
#include <vector>
using namespace std;


void dfs(const vector<string>& map, int i, int j, vector<vector<bool>>& visit) {
  int N = map.size();
  visit[i][j] = true;
  for (int di=-1;di<=1;++di) {
    for (int dj=-1;dj<=1;++dj) {
      if (di==0 && dj==0) continue;
      int ni = i+di, nj = j+dj;
      if (0 <= ni && ni < N && 0<=nj && nj < N && !visit[ni][nj] && map[ni][nj] == '1') {
        dfs(map, ni, nj, visit);
      }
    }
  }
}

int solve(const vector<string>& map) {
  int N = map.size();
  vector<vector<bool>> visit(N, vector<bool>(N, false));
  int group = 0;

  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      if (!visit[i][j] && map[i][j] == '1') {
        dfs(map, i, j, visit);
        group++;
      }
    }
  }
  return group;
}

int main() {
    int N, T = 1;
    string line;
    while (getline(cin, line)) {
      N = stoi(line);
      vector<string> map;
      for (int i=0;i<N;++i) {
        getline(cin, line);
        map.push_back(line);
      }
      cout << "Image number " << T++ << " contains " << solve(map) << " war eagles." << endl;   
    }
}