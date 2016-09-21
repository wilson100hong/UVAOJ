// NOTE: rectangle overlap test:
// http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Rec {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct Node {
  Node(const Rec& rec_) {
    rec = rec_;
  }
  Rec rec;
  vector<Node*> childs;
  int max;
  int min;
};

#define MIN numeric_limits<int>::min()
#define MAX numeric_limits<int>::max()

int min(int a, int b) {
  return a < b ? a : b;
}
int max(int a, int b) {
  return a > b ? a : b;
}
int min(const vector<Node*>& v) {
  int res = MAX;
  for (Node* node : v) {
    res = min(res, node->min);
  }
  return res;
}

int max(const vector<Node*>& v) {
  int res = MIN;
  for (Node* node : v) {
    res = max(res, node->max);
  }
  return res;
}

Node* build(const vector<vector<int>>& city, const Rec& rec) {
  Node* node = new Node(rec);
  if (rec.x1==rec.x2 && rec.y1==rec.y2) {
    node->min = node->max = city[rec.x1][rec.y1];
    return node;
  }

  // seprate region 
  int mx = (rec.x1 + rec.x2)/2;
  int my = (rec.y1 + rec.y2)/2;

  Node* child; 
  child = build(city, {rec.x1, rec.y1, mx, my});  // Top-Left
  node->childs.push_back(child);

  if (my+1 <= rec.y2) {
    child = build(city, {rec.x1, my+1, mx, rec.y2});  // Top-Right
    node->childs.push_back(child);
  }
  if (mx+1 <= rec.x2) {
    child = build(city, {mx+1, rec.y1, rec.x2, my});  // Bottom-Left
    node->childs.push_back(child);
  }
  if (mx+1 <= rec.x2 && my+1 <= rec.y2) {
    child = build(city, {mx+1, my+1, rec.x2, rec.y2});  // Bottom-Right
    node->childs.push_back(child);
  }

  // push up
  node->min = min(node->childs);
  node->max = max(node->childs);
  return node;
}

bool contains(const Rec& out, const Rec& in) {
  return (out.x1 <= in.x1 && in.x2 <= out.x2 &&
          out.y1 <= in.y1 && in.y2 <= out.y2);
}


bool in(const Rec& rec, int x, int y) {
  return (rec.x1 <= x && x <= rec.x2 &&
          rec.y1 <= y && y <= rec.y2);
}

bool overlap(const Rec& rec1, const Rec& rec2) {
  return rec1.x1 <= rec2.x2 && rec1.x2 >= rec2.x1 &&
         rec1.y1 <= rec2.y2 && rec1.y2 >= rec2.y1;
}

bool atpoint(const Rec& rec, int x, int y) {
  return rec.x1 == x && rec.x2 == x && rec.y1 == y && rec.y2 == y;
}

// query result
struct QR {
  int min;
  int max;
}; 

QR query(Node* root, const Rec& rec) {
  if (contains(rec, root->rec)) {
    return {root->min, root->max};
  }
  QR res = {MAX, MIN};
  for (Node* child : root->childs) {
    if (overlap(child->rec, rec)) {
      QR tmp = query(child, rec);
      res.min = min(res.min, tmp.min);
      res.max = max(res.max, tmp.max);
    }
  }
  return res;
}

void update(vector<vector<int>>& city, Node* root, int x, int y, int v) {
  if (atpoint(root->rec, x, y)) {
    root->min = root->max = v;
    return;
  }
  for (Node* child : root->childs) {
    if (in(child->rec, x, y)) {
      update(city, child, x, y, v);
    }
  }
  root->min = min(root->childs);
  root->max = max(root->childs);
}

int main() {
  int N;
  cin >> N;
  vector<vector<int>> city(N+1, vector<int>(N+1, 0));

  for (int i=1;i<=N;++i) {
    for (int j=1;j<=N;++j) {
      cin >> city[i][j];
    }
  }
  Node* root = build(city, {1, 1, N, N});
  int Q;
  cin >> Q;
  for (int q=0;q<Q;++q) {
    char op;
    cin >> op;
    if (op == 'q') {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      QR qr = query(root, {x1, y1, x2, y2});
      cout << qr.max << " " << qr.min << endl;
    } else if (op == 'c') {
      int x, y, v;
      cin >> x >> y >> v;
      update(city, root, x, y, v);
    }
  }
}
