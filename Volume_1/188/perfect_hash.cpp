#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
using namespace std;

typedef unsigned int uint;

bool UintCompare(const uint& u1, const uint& u2) {
  return u2 < u1;
}

uint min(const uint& u1, const uint& u2) {
  return u1 < u2 ? u1: u2;
}

uint NextC(uint C, uint w1, uint w2) {
  return min( ((C / w1) + 1) * w1, 
              ((C / w2) + 1) * w2);
}

struct Hashed{
  uint hash;
  uint score;
};

bool HashedCompare(const Hashed& h1, const Hashed& h2) {
  if (h1.hash == h2.hash) 
    return h1.score < h2.score;
  return h1.hash < h2.hash;
}

uint GetHashConstant(vector<uint>& scores) {
  sort(scores.begin(), scores.end(), UintCompare);
  
  int n = scores.size();
  uint C = scores[1]; // 2nd largest
  
  vector<Hashed> hashed_list;
  Hashed hashed;
  while (1) {
    hashed_list.clear();

    for (int i = 0; i < n; ++i) {
      hashed.score = scores[i];
      hashed.hash = (C / scores[i]) % n;
      hashed_list.push_back(hashed);
    }
    
    sort(hashed_list.begin(), hashed_list.end(), HashedCompare);
    uint next_C = C;
   
    // TODO: compute largest next_C
    int last_index = 0;
    int index = 1;
    while (index < n) {
      if (hashed_list[index].hash == hashed_list[last_index].hash) {
        next_C = max(next_C, 
                     NextC(C, hashed_list[index].score, hashed_list[last_index].score));
      } 
      last_index = index;
      index++;
    }
    if (next_C == C)
      break;
    C = next_C;
  }
  return C;
}

uint GetWordScore(string word) {
  uint sum = 0;
  for (int i = 0; i < word.length(); ++i) {
    int r = word[i] - 'a' + 1;
    sum = sum * 32 + r;
  }
  return sum;
}

void DumpScores(vector<uint>& scores) {
  for (int i = 0; i < scores.size(); ++i)
    cout << scores[i] << ", ";
  cout << endl;
}

int main() {
  string line;
  vector<uint> scores;
  bool first = true;
  while (getline(cin, line)) {
    cout << line << endl;
    scores.clear();
    stringstream ss(line);
    string word;
    while (ss >> word)
      scores.push_back(GetWordScore(word));
    cout << GetHashConstant(scores) << endl << endl;
  }
}
