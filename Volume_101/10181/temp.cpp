#include <array>
#include <map>
#include <iostream>
#include <utility>
using namespace std;

int main() {
  array<int, 3> arr = {2, 3, 4};
  pair<int, array<int, 3>> mypair = {3, arr};
  cout << mypair.first << endl;
  cout << arr[2] << endl;
  arr[1] = 9;
  cout << arr[1] << endl;
  typedef array<int, 3> ARR;
  map<int, ARR> mmm;
  mmm[3] = arr;
}
