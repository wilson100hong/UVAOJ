#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define IMF 1<<30

inline int max(int a, int b) {
  return a >= b ? a : b;
}

inline int min(int a, int b) {
  return a < b ? a : b;
}

struct Segment {
  int value;
  // range of [a, b]
  int a;  
  int b;
  int count;
};

Segment max(Segment s1, Segment s2) {
  return s1.count >= s2.count ? s1 : s2;
}

vector<Segment> S;
int N, M;

void init(vector<int>& values, vector<int>& counts) {
  S.clear();
  M = 1;
  while (M < values.size()) {
    M *= 2;
  }
  //cout << "M: " << M << endl;

  S.assign(M * 2, {IMF, N + 1, N + 1, 0});

  int index = 1;
  for (int i = 0; i < values.size(); ++i) {
    S[i + M] = {values[i], index, index + counts[i] - 1, counts[i]};
    index += counts[i];
  }

  for (int i = M - 1; i > 0; --i) {
    S[i] = max(S[i * 2], S[i * 2 + 1]);
    S[i].a = S[i * 2].a;
    S[i].b = S[i * 2 + 1].b;
  }
}

int query(int node, int a, int b) {
  if (a > S[node].b || b < S[node].a) {
    return 0;
  }

  int qa = max(a, S[node].a);
  int qb = min(b, S[node].b);

  if (qa == S[node].a && qb == S[node].b) {
    return S[node].count;
  }

  if (node >= M) {  // is leaf
    return S[node].count > 0 ? qb - qa + 1 : 0;
  }

  return max(query(node * 2, qa, qb),
             query(node * 2 + 1, qa, qb));
}

int main() {
  int q, value, prev;
  while (1) {
    cin >> N;
    if (N == 0)
      break;
    cin >> q;

    vector<int> values;
    vector<int> counts;
    int prev = 20000000;
    for (int i = 0; i < N; ++i) {
      cin >> value;
      if (value != prev) {
        values.push_back(value);
        counts.push_back(1);
      } else {
        counts[values.size() - 1]++;
      }
      prev = value;
    }

    init(values, counts);
    for (int i = 0; i < q; ++i) {
      int a, b;
      cin >> a >> b;
      cout << query(1, a, b) << endl;
    }
  }
}
