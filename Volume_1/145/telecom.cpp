#include <iostream>
using namespace std;

int PRICE[4][5] = {
  {10, 25, 53, 87, 144},  // 8 - 18
  {6, 15, 33, 47, 80}, //18 - 22
  {2,  5, 13, 17, 30}, //22 - 24
  {2,  5, 13, 17, 30}
  }; // 24,0 - 8

int STEP_BOUND[4] = {8*60, 18*60, 22*60, 24*60};
int END_OF_THE_DAY = 24*60;

int GetStep(int time) {
  if (STEP_BOUND[0] <= time && time < STEP_BOUND[1])
    return 0;
  else if (STEP_BOUND[1] <= time && time < STEP_BOUND[2])
    return 1;
  else if (STEP_BOUND[2] <= time && time <= STEP_BOUND[3])
    return 2;
  else
    return 3;
}


void Charge(int start, int end, int(&duration)[4]) {
  if (start > end) {
    cout << "IMPOSSIBLE!" << endl;
    return ;
  }
  // start always <= end
  while (GetStep(start) != GetStep(end)) {
    int step = GetStep(start);
    duration[step] += (STEP_BOUND[(step+1)%4] - start);  
    start = STEP_BOUND[(step+1)%4];
  }
  int step = GetStep(start);
  duration[step] += (end - start);
}

int main() {
  char c;
  string number;
  int begin_hr, begin_min, end_hr, end_min;
  int duration[4];

  while (cin >> c) {
    if (c == '#') break;
    cin >> number >> begin_hr >> begin_min >> end_hr >> end_min;
    int begin = begin_hr*60 + begin_min;
    if (begin == END_OF_THE_DAY)
      begin = 0;
    int end = end_hr*60 + end_min;
  
    for(int i=0;i<4;++i)
      duration[i] = 0;
    
    if (end <= begin) {
      //cout << "CROSS DAY" << endl;
      Charge(begin, END_OF_THE_DAY, duration);
      begin = 0;  // begin of the day
    }
    Charge(begin, end, duration);
 
    int sum = 0;
    for (int i=0;i<4;++i) {
      sum += PRICE[i][(int) c-'A'] * duration[i];
    }

    cout.fill(' ');
    cout.width(10); cout << number;
    cout.width(6); cout << duration[0];
    cout.width(6); cout << duration[1];
    cout.width(6); cout << duration[2] + duration[3];
    cout.width(3); cout << c;
    int dollor = sum / 100;
    cout.width(5); cout << dollor;
    int cents = sum % 100;
    cout << ".";
    cout.width(2); cout.fill('0'); cout << cents << endl;
  }
}
