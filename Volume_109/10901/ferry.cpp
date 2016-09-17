// TODO: WA
// Trap: when you wait, you may load multiple cars because they can come at the same time
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

struct Car{
  int index;
  int arrival;
};

#define LEFT 0
#define RIGHT 1

int main() {
  int cases;
  eatline() >> cases;
  bool first = true;
  while (cases--) {
    int N, T, M;
    eatline() >> N >> T >> M;
    vector<int> unloads(M, -1);
    vector<queue<Car>> banks(2, queue<Car>());
    for (int m=0; m<M; ++m) {
      int arrival;
      string side;
      eatline() >> arrival >> side; 
      Car car = {m, arrival};
      if (side == "left") {
        banks[LEFT].push(car);
      } else {
        banks[RIGHT].push(car);
      }
    }

    queue<Car> boat;
    int time = 0;
    int side = LEFT;
    int round = 0;
    while (!banks[LEFT].empty() || !banks[RIGHT].empty() || !boat.empty()) {
      // 1. unload
      while (!boat.empty()) {
        Car car = boat.front();
        boat.pop();
        unloads[car.index] = time;
      }
      // 2. decide loading time
      int other_side = (side+1)%2;
      if (banks[side].empty() ||
          banks[side].front().arrival > time && 
          (!banks[other_side].empty() && banks[other_side].front().arrival < banks[side].front().arrival)) {
        // 2.1 go to other side
        if (banks[other_side].front().arrival > time) {
          time = banks[other_side].front().arrival;
        } 
      } else {
        // 2.2 wait at this side, if needed
        if (banks[side].front().arrival > time) {
          time = banks[side].front().arrival;
        }
        while (!banks[side].empty() &&
               banks[side].front().arrival <= time &&
               boat.size() < N) {
          Car car = banks[side].front();
          banks[side].pop();
          boat.push(car);
        }
      }
      side = other_side;
      time += T;
    }
    if (!first) cout << endl;
    first = false;
    for (int unload : unloads) {
      cout << unload << endl;
    }
  }

}
