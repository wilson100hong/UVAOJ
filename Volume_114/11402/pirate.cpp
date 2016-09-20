// Trap: the MAX_TREE is 2^21 !
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std; stringstream SS; stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

#define MAX_N 1025000
bool pirates[MAX_N];
#define MAX_TREE 2100000
int tree[MAX_TREE];
char lazy[MAX_TREE];

int N=0;  // total number of pirates

void dump() {
  for (int i=0;i<N;++i) {
    cout << pirates[i];
  }
  cout << endl;
}

int set_pirates(int T, const string& str) {
  for (int t=0;t<T;++t) {
    for (int i=0;i<str.size();++i) {
      pirates[N++] = str[i]-'0';
    }
  }
}

void push_up(int root) {
  tree[root] = tree[root<<1] + tree[root<<1|1];
}

void build(int root, int l, int r) {
  char old = lazy[64];

  // TODO: this will mutate lazy. why?
  if (l == r) {
    tree[root] = pirates[l];
    return;
  }
  int m = (l+r)/2;
  build(root<<1, l, m);
  build(root<<1|1, m+1, r);
  push_up(root);
}

void cast(int root, int l, int r, char spell) {
  if (spell == 'F') {
    tree[root] = r-l+1;
    lazy[root] = spell;
  } else if (spell == 'E') {
    tree[root] = 0;
    lazy[root] = spell;
  } else if (spell == 'I') {
    tree[root] = (r-l+1) - tree[root];
    if (lazy[root] == 0) {
      lazy[root] = 'I';
    } else if (lazy[root] == 'I') {
      lazy[root] = 0;
    } else if (lazy[root] == 'F') {
      lazy[root] = 'E';
    } else if (lazy[root] == 'E') {
      lazy[root] = 'F';
    } else {
      cout << "YOU STUPID!" << endl;
    }
  } else {
    cout << "spell: " << static_cast<int>(spell) << endl;
    cout << "root: " << root << " [" << l << "," << r << "]" << endl;
    cout << "YOU STUPID" << endl;
  }
}

void push_down(int root, int l, int r) {
  int m = (l+r)/2;
  cast(root<<1, l, m, lazy[root]);
  cast(root<<1|1, m+1, r, lazy[root]);
  lazy[root]=0;  // reset
}

int query(int root, int l, int r, int a, int b) {
  if (a<=l && r<=b) {
    return tree[root];
  }
  if (lazy[root] != 0) {
    push_down(root, l, r);
  }
  // so lazy[root] is 0 now
  int m = (l+r)/2;
  int res = 0;
  if (a<=m) {
    res += query(root<<1, l, m, a, b);
  }
  if (m<b) {
    res += query(root<<1|1, m+1, r, a, b);
  }
  return res;
}

void update(int root, int l, int r, int a, int b, char spell) {
  //cout << "update root: " << root << " range: [" << l << "," << r << "]" << endl;
  if (a<=l && r<= b) {
    // TODO:  lazy[root]?
    cast(root, l, r, spell);
    return;
  }
  if (lazy[root] != 0) {
    push_down(root, l, r);
  }
  int m = (l+r)/2;
  int res = 0;
  if (a<=m) {
    update(root<<1, l, m, a, b, spell);
  }
  if (m<b) {
    update(root<<1|1, m+1, r, a, b, spell);
  }
  push_up(root);
}

int main() {
  int cases;
  eatline() >> cases;
  for (int cs=0;cs<cases;++cs) {
    memset(tree, 0, MAX_TREE);
    memset(lazy, 0, MAX_TREE);

    N = 0;
    int M;
    eatline() >> M;
    for (int m=0;m<M;++m) {
      int T;
      eatline() >> T;
      string str;
      getline(cin, str);
      set_pirates(T, str);
    }

    build(1, 0, N-1);

    cout << "Case " << cs+1 << ":" << endl;
    int Q;
    eatline() >> Q;
    int question = 1;
    for (int q=0;q<Q;++q) {
      char spell;
      int a, b;
      // NOTE: a and b are 0-based index
      eatline() >> spell >> a >> b;
      if (spell == 'S') {
        cout << "Q" << question << ": " << query(1, 0, N-1, a, b) << endl;
        question++;
      } else {
        update(1, 0, N-1, a, b, spell);
      }
    }
  }
}
