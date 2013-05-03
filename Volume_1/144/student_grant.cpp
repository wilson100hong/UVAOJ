#include <iostream>

using namespace std;

int student[25];

int main() {
  int N, K;
  while (cin >> N >> K) {
    if (N == 0 && K == 0)
      break;
    for (int i=0;i<N;++i)
      student[i] = 40;
    
    // Do simulation here
    int index = 0;
    int complete = 0;
    int move = 1;
    int store = 0;
    while (complete < N) {
      if (store == 0) {
        store += move;
        move++;
        if (move == K+1)
          move = 1;
      }

      while(student[index] ==0) {
        index++;
        index %= N;
      }

      if (store >= student[index]) {
        store -= student[index]; 
        student[index ] = 0;
        complete++;
        cout.width(3);
        cout << index + 1; 
      } else {
        student[index] -= store;
        store = 0;
      }
      
      index++;
      index %= N;
    }
    cout << endl;
  }
}
