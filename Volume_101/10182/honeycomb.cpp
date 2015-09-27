#include <iostream>

using namespace std;

// axis the direction from a grid
// clockwise from S -> SW -> NW -> N -> NE -> SE
//   2   3   4
//    \  |  /
//    /  |  \
//   1   0   5
#define AXIS_S   0
#define AXIS_SW  1
#define AXIS_NW  2
#define AXIS_N   3
#define AXIS_NE  4
#define AXIS_SE  5
#define NUM_AXIS 6

// for grid between sector S -> SW, the direction is NW
int toward[] = { 2, 3, 4, 5, 0, 1};

int dx[] = {0, -1, -1, 0, 1, 1};
int dy[] = {1, 1, 0, -1, -1, 0};
// shell is a list of grids which has same distance from center of hive. 
// For example, grids 2~7 are in shell 1, grids 8 ~ 19 ard in shell 2.

void solve(int grid) {
  int cur = 1, dist = 0, axis = AXIS_SE;
  while (cur < grid) {
    // count next grid
    int n_axis = axis + 1;
    if (n_axis == NUM_AXIS) {
      n_axis = 0;
      dist++;
    }
    int next = cur + dist;
    if (next < grid) {
      axis = n_axis;
      cur = next;
    } else {
      break;
    } 
  }
  int rest = grid - cur;
  int x = dx[axis]*dist , y = dy[axis]*dist;
  while (rest-- > 0) {
    x += dx[toward[axis]];
    y += dy[toward[axis]];
  }
  cout << x << " " << y << endl;
}

int main() {
  int grid;
  while (cin >> grid) {
    solve(grid);
  }
}
