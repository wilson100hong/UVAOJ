#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <sstream>
using namespace std;
#define MAX_TIME 18000

// return 0 if current green
int NextGreenTime(int sec, int half_life) {
  int period = half_life * 2;
  int q = sec / period;
  int r = sec % period;
  if (0 <= r && r < half_life - 5)
    return 0;
  else
    return (q + 1) * period;
}

// return the time when all light is green,
// or -1 if >= 18000 (including impossible)
int Simulation(const vector<int>& lights) {
  int sec = 2 * lights[0];
  vector<int> red_next_green_moment;
  while (sec <= MAX_TIME) {
    red_next_green_moment.clear();
    for (int i=0;i<lights.size();++i) {
      int next_green = NextGreenTime(sec, lights[i]); 
      if (next_green > 0)
        red_next_green_moment.push_back(next_green);
    }
    if (red_next_green_moment.empty()) 
      return sec;

    sort(red_next_green_moment.begin(), red_next_green_moment.end());
    sec = red_next_green_moment[red_next_green_moment.size()-1];
  }
  return -1;
}

void PrintTime(int seconds) {
  if (seconds < 0 || seconds > 18000) {
    cout << "Signals fail to synchronise in 5 hours" << endl;
    return;
  }
  int hr = seconds / 3600;
  seconds %= 3600;
  int min = seconds / 60;
  seconds %= 60;
  cout.width(2);
  cout.fill('0');
  cout << hr << ":";
  cout.width(2);
  cout.fill('0');
  cout << min << ":";
  cout.width(2);
  cout.fill('0');
  cout << seconds;
  cout << endl; 
}

int main() {
  // read input
  vector<int> lights;
  int half_life;
  while (cin >> half_life) {
    if (half_life == 0) {
      if (lights.size() >= 2) {
        sort(lights.begin(), lights.end());
        int seconds = Simulation(lights);
        PrintTime(seconds);
      }
      lights.clear();
    } else {
      lights.push_back(half_life);
    }
  }
}
