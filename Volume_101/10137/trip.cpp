#include <iostream>
using namespace std;
int main() {
  int n;
  string line;
  while (cin >> n) {
    if (n == 0)
      break;
    int* students = new int[n];
    int cnt = 0;
    long long sum = 0;
    getline(cin, line);
    while (cnt < n) {
      getline(cin, line);
//      cout << line << endl;
      int aa = 0;
      for (int i = 0; i < line.length(); ++i) {
        if ('0' <= line[i] && line[i] <= '9') {
          aa = aa * 10 + (int) (line[i] - '0');
        }
      }
      students[cnt] = aa;
      sum += students[cnt++];
    }

//    cout << "sum " << sum << endl;
    int avg = sum / n;
    int remain = sum % n;
 //   cout << "avg " << avg << endl;
  //  cout << "rem " << remain << endl;   
    
    int numbig = 0;
    int sumexg = 0;
    for (int i = 0; i < n; ++i) {
   //   cout << "studens[ " << i << "] : " << students[i] << endl;
      if (students[i] > avg) {
        numbig++;
      } else {
        sumexg += (avg - students[i]);
      }
    }
    if (remain > numbig) {
      remain = remain - numbig;
    } else {
      remain = 0;
    }
    cout << "$";
    int money = sumexg + remain;
    int dollars = money / 100;
    cout << dollars << ".";
    int cents = money % 100;
    if (cents < 10)
      cout << "0";
    cout << cents << endl;
    //float dollars = (float) money / 100;
    //cout.setf(ios::fixed,ios::floatfield);
    //cout.precision(2);

    delete students;
  }

  return 0;
}
