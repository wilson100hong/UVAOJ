#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define MAX 50
#define BG -1
#define DICE -2
#define DOT -3

int W, H;
int image[MAX][MAX];
int dfs1[MAX][MAX];
int dfs2[MAX][MAX];

int Pixel2Int(char c) {
  if (c == '.')
    return BG;
  else if (c == '*')
    return DICE;
  else if (c == 'X')
    return DOT;
  else
    return -100;
}

#define NOT_VISIT -1
#define IMPOSSIBLE -2

char Int2Pixel(int n) {
  if (n == IMPOSSIBLE) return 'X';
  return (char) ('0' + n);
}

void Dump(int array[MAX][MAX]) {
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      cout << Int2Pixel(array[h][w]);
    }
    cout << endl;
  }
  cout << endl;
}


int dh[] = {-1, 0, 1, 0};
int dw[] = {0, 1, 0, -1};

void DFS(int array[MAX][MAX], int h, int w, int color) {
  array[h][w] = color;
  for (int i = 0; i < 4; ++i) {
    int hh = h + dh[i];
    int ww = w + dw[i];
    if (0 <= hh && hh < H && 0 <= ww && ww < W &&
        array[hh][ww] == NOT_VISIT) {
      DFS(array, hh, ww, color);
    }
  }
}

void Solve() {
  // 1. Distinguish BG and DICE+DOT
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      if (image[h][w] == DICE || image[h][w] == DOT) {
        dfs1[h][w] = NOT_VISIT;
      } else {  // BG
        dfs1[h][w] = IMPOSSIBLE;
      }
    }
  }

  int num_dice = 0;
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      if (dfs1[h][w] == NOT_VISIT) {
        DFS(dfs1, h, w, num_dice);
        num_dice++;
      }
    }
  }

  vector<int> numbers(num_dice, 0);

  // 2. Detect the # of DOTs in a DICE
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      if (image[h][w] == DOT) {
        dfs2[h][w] = NOT_VISIT;
      } else {  // DICE or BG
        dfs2[h][w] = IMPOSSIBLE;
      }
    }
  }
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      if (dfs2[h][w] == NOT_VISIT) {
        int dice = dfs1[h][w];
        int num_dot = numbers[dice]++;
        DFS(dfs2, h, w, num_dot);
      }
    }
  }

  sort(numbers.begin(), numbers.end());

  for (int i = 0; i < numbers.size(); ++i) {
    if (i != 0) cout << " ";
    cout << numbers[i];
  }
  cout << endl;
}

int main() {
  int round = 0;
  while (1) {
    cin >> W >> H;
    if (W == 0 && H ==0)
      break;
    string line;
    getline(cin, line);
    for (int h = 0; h < H; ++h) {
      getline(cin, line);
      for (int w = 0; w < W; ++w) {
        image[h][w] = Pixel2Int(line[w]);
      }
    }
    cout << "Throw " << ++round << endl;
    Solve();
    cout << endl;
  }
}
