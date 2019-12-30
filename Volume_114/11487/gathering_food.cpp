#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <limits>

using namespace std;

typedef unsigned long long ULL;
constexpr int kMax= numeric_limits<int>::max();

int ToIndex(int N, pair<int, int> pos) {
  return pos.first * N + pos.second;
}

struct Elem {
  int r;
  int c;
  int dist;
};

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

pair<int, ULL> BFS(const vector<vector<char>>& forest, const vector<pair<int,int>>& letters, int u, int v) {
  const int N = forest.size();

  vector<vector<int>> dists(N, vector<int>(N, kMax));
  vector<vector<ULL>> ways(N, vector<ULL>(N, 0));

  queue<Elem> Q;
  Q.push({letters[u].first, letters[u].second, 0});

  while (!Q.empty()) {
    Elem top = Q.front();
    Q.pop();

    // Update dists[] and ways[]
    if (top.dist > dists[top.r][top.c]) continue;

    if (top.dist < dists[top.r][top.c]) {
      dists[top.r][top.c] = top.dist;
      ways[top.r][top.c] = 0;
    }
    ways[top.r][top.c] += 1;

    if (top.r == letters[v].first && top.c == letters[v].second) {
      continue;
    }

    for (int d=0;d<4;++d) {
      int nr = top.r + dr[d], nc = top.c + dc[d];
      if (0<=nr && nr<N && 0<=nc && nc<N
          && forest[nr][nc] != '#'
          && (forest[nr][nc] == '.' || forest[nr][nc] - 'A' <= v)
          && (top.dist + 1 <= dists[nr][nc])) {
        Q.push({nr, nc, top.dist + 1});
      }
    }
  }
  
  if (dists[letters[v].first][letters[v].second] == kMax) return {};
  return {
    dists[letters[v].first][letters[v].second], 
    ways[letters[v].first][letters[v].second]
  };
}

pair<int, ULL> Solve(const vector<vector<char>>& forest, int letter_cnt) {
  int N = forest.size();
  vector<pair<int, int>> letters(letter_cnt, {-1,-1});
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      if ('A' <= forest[i][j] && forest[i][j] <= 'Z') {
        int index = forest[i][j] - 'A';
        letters[index] = {i, j};
      }
    }
  }

  pair<int, ULL> ans = {0, 1};
  for (int i=0;i<letters.size() - 1;++i) {
    int j = i+1;
    pair<int, ULL> temp = BFS(forest, letters, i, j);
    if (temp.second == 0) return {kMax, 0};
    ans.first += temp.first;
    ans.second = (ans.second * (temp.second % 20437)) % 20437;
  }
  return ans;
}


int main() {
  int N;
  int case_num = 1;
  while (cin >> N) {
    if (N == 0) break;
    vector<vector<char>> forest(N, vector<char>(N, '.'));
    int letter_cnt = 0;
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        cin >> forest[i][j];
        if ('A' <= forest[i][j] && forest[i][j] <= 'Z') {
          letter_cnt = max(letter_cnt, forest[i][j] - 'A' + 1);
        }
      }
    }
    pair<int, int> ans = Solve(forest, letter_cnt);
    cout << "Case " << case_num++ << ": ";
    if (ans.second == 0) {
      cout << "Impossible";
    } else {
      cout << ans.first << " " << ans.second;
    }
    cout << endl;
  }
}
