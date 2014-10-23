#include <iostream>
#include <vector>

using namespace std;

#define MAX 100
#define NON_VISIT -1
#define LAND -2

int N, M;
int index = 0;
int cells[MAX][MAX];
int dn[] = {-1, -1, -1, 0, 1, 1,  1,  0};
int dm[] = {-1,  0,  1, 1, 1, 0, -1, -1};

int DFS(int n, int m) {
  cells[n][m] = index;  // coloring
  int area = 1;
  for (int i = 0; i < 8; ++i) {
    int nn = n + dn;
    int mm = m + dm;
    if (0 <= nn && nn < N && 0 <= mm && mm < M &&
        celss[nn][mm] == NON_VISIT) {
      area += DFS(nn, mm);
    }
  }
  return area;
}


int main() {
  int rounds;
  cin >> rounds;
  vector<string> land_strs;
  vector<string> queries;
  vector<int> areas;

  string line;
  getline(cin, line); 
  getline(cin, line); 

  while (rounds-- > 0) {
    land_strs.clear();
    queries.clear();
    while(getline(cin, line) && !line.empty()) {
      if (line[0] =='W' || line[0] == 'L') {
        land_strs.push_back(line);
      } else {
        queries.push_back(line);
      }
    }

    N = land_strs.size(), M = land_strs[0].size();
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < M; ++m) {
        if (land_strs[n][m] == 'W') {
          cells[n][m] = NON_VISIT;
        } else if (land_strs[n][m] == 'L') {
          cells[n][m] = LAND;
        }
      }
    }

    index = 0;
    areas.clear();
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < M; ++m) {
        if (cells[n][m] == NON_VISIT) {
          int area = DFS(n, m);
          lakes.push_back(area);
          index++;
        }
      }
    }
  }
}
