#include <iostream>
#include <cstdint>
using namespace std;

int32_t convert(int32_t input) {
  int32_t result = 0;
  for (int i=0; i<4; ++i) {
    int32_t block = input & 255;
    result |= block;
    if (i < 3) {
      input = input >> 8;
      result = result << 8;
    }
  }
  return result;
}

int main() {
  int32_t input;
  while (cin >> input) {
    cout << input << " converts to " <<  convert(input) << endl;
  }
}
