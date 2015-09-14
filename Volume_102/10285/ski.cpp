#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define UNVISIT -1
struct Label{
  int post;
  int index;
};

bool compareLabel(const Label& l1, const Label& l2) {
  return l1.post > l2.post;
}

int dfs(const vector<vector<int>>& graph, int index, int post, vector<Label>& labels) {
  for (int neighbor : graph[index]) {
    if (labels[neighbor].post == UNVISIT) {
      post = dfs(graph, neighbor, post, labels);
    }
  }
  labels[index].post = post++;
  return post;
};

struct Field {
  int r;
  int c;
  int h;
  int dist;
};

int dr[] = {-1, 0, 1,  0};
int dc[] = {0,  1, 0, -1};
int R, C;

int rc2i(int r, int c) {
  return r * C + c;
}

int longest_path(vector<Field>& resort) {
  vector<vector<int>> graph(resort.size(), vector<int>());
  vector<Label> labels(resort.size(), {UNVISIT});
  // 1. build graph and labels
  int r, c;
  for (int i = 0; i < resort.size(); ++i) {
    labels[i].index = i;
    int r = resort[i].r, c = resort[i].c, h = resort[i].h;
    for (int d = 0; d < 4; ++d) {
      int nr = r + dr[d], nc = c + dc[d];
      int ni = rc2i(nr, nc);
      if (0 <= nr && nr < R && 0 <= nc && nc < C && h > resort[ni].h) {
        graph[i].push_back(ni);
      }
    }
  }

  // 2. topological sort 
  int post = 0;
  for (int i = 0; i < resort.size(); ++i) {
    if (labels[i].post == UNVISIT) {
      post = dfs(graph, i, post, labels);
    }
  }
  sort(labels.begin(), labels.end(), compareLabel);

  // 3. Update dist for all neighbors 
  int longest = 0;
  for (Label& label : labels) {
    int i = label.index;
    int dist = resort[i].dist;
    if (dist > longest) longest = dist;
    for (int j : graph[i]) {
      if (resort[j].dist < dist + 1) {
        resort[j].dist = dist + 1;
      }
    } 
  }
  return longest;
}

int main() {
  int N;
  cin >> N;
  for (int n = 0; n < N; ++n) {
    string name;
    cin >> name >> R >> C;
    vector<Field> resort;
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        int h; 
        cin >> h;
        resort.push_back({r, c, h, 1});
      }
    }
    cout << name << ": " << longest_path(resort) << endl;
  }
}
