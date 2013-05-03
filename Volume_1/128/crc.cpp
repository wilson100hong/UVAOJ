#include <iostream>
#include <iomanip>
using namespace std;

#define G 34943

int crc(string msg) {
  unsigned long long sum = 0;
  for (int i = 0; i < msg.length() && i < 1024; ++i) {
    sum = sum << 8; // * 256
    sum += (int) msg[i];
    sum %= G;
  }
  sum = sum << 16;  // * 256 * 256
  sum %= G;
  return (G - sum) % G;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line.length() > 0 && line[0] == '#')
      break;
    int code = crc(line);
    int top = code / 256;
    int btm = code % 256;
    cout << hex << setfill('0') << setw(2) << uppercase << top << " ";
    cout << hex << setfill('0') << setw(2) << uppercase << btm << endl;
  }
}
