#include <iostream>
#include <sstream>
using namespace std;

int max(int a, int b) {
  return a >= b ? a : b;
}

int main() {
  int n;
  cin >> n;
  int* truth = new int[n];
  int* answer = new int[n];
  int* score = new int[n];
  int i, j = 0;
  while (i < n) {
    cin >> j;
    truth[j - 1] = i++;
  }
  string line;
  getline(cin, line);
  
  while (getline(cin, line)) {
    stringstream ss(line);
    i = 0;
    while (i < n) {
      ss >> j;
      answer[j - 1] = i;
      score[i++] = 0;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (truth[i] == answer[j]) { 
          score[j] = 1 + (j > 0 ? score[j - 1] : 0);   
        } else {
          score[j] = max( (j > 0 ? score[j - 1] : 0), score[j]);
        }
      }
    }
    cout << score[n - 1] << endl;
  }
}
