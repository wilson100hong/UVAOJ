#include <iostream>
#include <vector>
using namespace std;

int to_score(const string& word) {
  int n = word.size();
  if (n <= 2) return 0;
  if (n >= 8) return 11;
  if (n == 7) return 5;
  if (n == 6) return 3;
  if (n == 5) return 2;
  return 1;  // 3 or 4
}

int di[] = {-1, -1, -1,  0, 0, 1, 1, 1};
int dj[] = {-1,  0,  1, -1, 1,-1, 0, 1};

bool dfs(const vector<string>& boggle, int i, int j, const string& word, int pos, int visit[4][4]) {
  visit[i][j] = 1;
  pos++;
  if (pos == word.size()) return true;
  for (int d=0;d<8;++d) {
    int ni = i + di[d];
    int nj = j + dj[d];
    if (0 <= ni && ni < 4 && 0 <= nj && nj < 4 && !visit[ni][nj] && boggle[ni][nj] == word[pos]) {
      if (dfs(boggle, ni, nj, word, pos, visit)) {
        return true;
      }
    }
  }
  visit[i][j] = 0;
  return false;
}

bool search(const vector<string>& boggle, const string& word) {
  for (int i=0;i<4;++i) {
    for (int j=0;j<4;++j) {
      int visit[4][4] = {0};
      if (boggle[i][j] == word[0]) {
        if (dfs(boggle, i, j, word, 0, visit)) {
          return true;
        }
      }
    }
  }
  return false;
}

int solve(const vector<string>& boggle, const vector<string>& words) {
  int score = 0;
  for (const auto& word : words) {
    if (search(boggle, word)) {
      score += to_score(word);
    }
  }
  return score;
}

int main() {
  int T;
  cin >> T;
  int ts = 1;
  string line;
  while (ts <= T){
    vector<string> boggle(4);
  
    for (int i=0;i<4;++i) {
      cin >> boggle[i];
      //cout << boggle[i] << endl;
    }
    //cout << "----" << endl;
    int W;
    cin >> W;
    vector<string> words;
    for (int i=0;i<W;++i) {
      cin >> line;
      words.push_back(line);
      //cout << words[words.size()-1] << endl;
    }

    int score = solve(boggle, words);
    cout << "Score for Boggle game #" << ts++ << ": " << score << endl;
  }
}
