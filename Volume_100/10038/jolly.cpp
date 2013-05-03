#include <iostream>
#include <sstream>
using namespace std;

int abs(int n) {
  if (n < 0) {
    return -n;  
  }  
  return n;
}

int main() {
  string line;
  while(getline(cin, line)) {
    istringstream in(line, istringstream::in);  
    bool isJolly = true;
    int size;
    in >> size;
    if (size <= 0) {
      isJolly = false;
    } else {
      // Init occur
      int* occur = new int[size];
      for (int i = 0; i < size; i++) {
        occur[i] = 0; 
      }
      

      int n = size;
      int a, b, diff;
      in >> a;
      n--;
      while (n > 0) {
        in >> b;
        diff = abs(a - b);

        if (diff < size  && occur[diff] == 0) {
          occur[diff]++;
        } else {
          isJolly = false;
          break;
        } 
        a = b;
        n--;
      }
     
      delete occur;

      if (isJolly) {
        cout << "Jolly" << endl;
      } else {
        cout << "Not jolly" << endl;
      }
    }
  }
  return 0;
}
