#include <iostream>
#include <string>
using namespace std;
int abs(int n) {
    return n >=0 ? n : -n;
}
int main() {
  int len;
  string line;
  int turn = 1;
  while (cin >> len && len != 0) {
    //getline(cin, line);
    int* wall = new int[len];
    int sum = 0;
    for (int i = 0; i < len; ++i) {
    	cin >> wall[i];
        sum += wall[i];
    }
    int h = sum / len;
    int move = 0;
    for (int i = 0; i < len; ++i) {
    	move += wall[i] > h ? wall[i] - h : 0;
    }
    delete wall;
    cout << "Set #" << turn++ << endl; 
    cout << "The minimum number of moves is " << move << "." << endl;
    cout << endl;
  }
  
  return 0;
}
