#include <iostream>
#include <random>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

enum Color{ 
  RED = 0,
  BLACK = 1
};

template <class T>
class RBNode {
public:
  typedef RBNode<T> Node;

  RBNode() {}
  RBNode(T _key, Color _color, Node* _parent, Node* _left, Node* _right, int _h) 
      : key(_key), color(_color), parent(_parent), left(_left), right(_right), height(_h) {}

  inline bool is_root() { return parent == nullptr; }
  inline bool is_left() { return is_root() ? false : this == parent->left; }
  inline bool is_right() { return is_root() ? false : !is_left(); }
  
  inline Node* grand() { return is_root() ? nullptr : parent->parent;}

  inline Node* sibling() {
    if (is_root()) return nullptr;
    return is_left() ? parent->right : parent->left;
  }

  Node* uncle() {
    Node* g = grand();
    if (g == nullptr) return nullptr;
    return parent->is_left() ? g->right : g->left;
  }

  Color color;
  T key;
  Node* parent;
  Node* left;
  Node* right;
  int height = 0;
};

template <class T>
class RBTree {
public:
  typedef RBNode<T> Node;
  RBTree() {
    NIL = new Node();
    NIL->color = Color::BLACK;
  }

  ~RBTree() {
    release(root);
    delete NIL;
  }

  size_t size() { return sz;}
  int height() { return nil(root) ? 0 : root->height; }
  int slow_height() { return rec_get_height(root); }

  // Recursive search
  Node* search(T key) {
    Node* n = root;
    while (!nil(n)) {
      if (n->key == key) return n;
      n = n->key > key ? n->left : n->right;
    }
    return nullptr;
  }

  void insert(T key) {
    Node *node = root, *parent = nullptr;
    while (!nil(node)) {
      parent = node;
      if (node->key == key) {
        cout << "Key " << key << " already exist" << endl;
        return;
      }
      node = node->key > key ? node->left : node->right;
    }

    node = new_node(key, parent);
    sz++;
    if (parent == nullptr) {
      root = node;
      node->color = Color::BLACK;
      return;
    }

    if (parent->key > key) {
      parent->left = node;
    } else {
      parent->right = node;
    }
    update_height(node);
    insert_adjust(node);
  }

  void erase(T key) {
    // TODO: adjust height
    Node* n = search(key);
    if (nil(n)) {
      cout << "key does not exist" << endl;
      return;
    }

    Node* s = successor(n);
    if (!nil(s)) {
      swap(n->key, s->key);
      n = s;
    }
    erase_one_child(n);
  }


private:
  bool nil(Node* n) { return n == NIL || n == nullptr; }

  void release(Node* n) {
    if (nil(n)) {
      return;
    }

    if (!nil(n->left)) {
      release(n->left);
    }
    if (!nil(n->right)) {
      release(n->right);
    }
    delete n;
  }

  Node* new_node(T key, Node* p) {
    return new Node(key, Color::RED, p, NIL, NIL, 1);
  }

  Node* successor(Node* n) {
    if (nil(n) || nil(n->right)) {
      return  nullptr;
    }
    Node* t = n->right;
    while (!nil(t->left)) {
      t = t->left;
    }
    return t;
  }

  void rotate_left(Node* n) {
    if (n->is_root()) return;
    Node *p = n->parent, *g = n->grand(), *y = n->left;
    p->right = y;
    if (!nil(y)) y->parent = p;
    n->left = p;
    p->parent = n;
    n->parent = g;
    if (g == nullptr) {
      root = n;
    } else {
      if (g->left == p) g->left = n;
      else g->right = n;
    }
  }

  void rotate_right(Node* n) {
    if (n->is_root()) return;
    Node *p = n->parent, *g = n->grand(), *y = n->right;
    p->left = y;
    if (!nil(y)) y->parent = p;
    n->right = p;
    p->parent = n;
    n->parent = g;
    if (g == nullptr) {
      root = n;
    } else {
      if (g->left == p) g->left = n;
      else g->right = n;
    }
  }

  void insert_adjust(Node* n) {
    if (n->parent == nullptr) {
      root = n;
      n->color = Color::BLACK;
      return;
    }
    Node *p = n->parent;
    if (p->color == Color::BLACK) return;

    // parent is RED, must have grand
    Node *u = n->uncle(), *g = n->grand();
    if (u->color == Color::RED) {
      p->color = Color::BLACK;
      u->color = Color::BLACK;
      g->color = Color::RED;
      insert_adjust(g);
    } else {
      if (p == g->left) {
        if (n == p->right) {
          rotate_left(n);
          update_height(p);
          rotate_right(n);
          update_height(g);
          n->color = Color::BLACK;
        } else {
          rotate_right(p);
          update_height(g);
          p->color = Color::BLACK;
        }
      } else {
        if (n == p->left) {
          rotate_right(n);
          update_height(p);
          rotate_left(n);
          update_height(g);
          n->color = Color::BLACK;
        } else {
          rotate_left(p);
          update_height(g);
          p->color = Color::BLACK;
        }
      }
      g->color = Color::RED;
    }
  }

  void erase_one_child(Node* n) {
    Node* c = nil(n->left) ? n->right : n->left;
    Node* p = n->parent;
    if (p == nullptr) {  // n is root
      if (nil(c)) {
        root = nullptr;
      } else {
        root = c;
        c->parent = nullptr;
        c->color = Color::BLACK;
      }
      delete n;
      return;
    }

    c->parent = p;
    if (n == p->left) {
      p->left = c;
    } else {
      p->right = c;
    }
    delete n;
    update_height(c);

    if (n->color == Color::BLACK) {
      if (c->color == Color::RED) {
        c->color = Color::BLACK;
      } else {
        erase_adjust(c);
      }
    }
  }

  void erase_adjust(Node* n) {
    Node* p = n->parent;
    if (p == nullptr) {
      root = n;
      n->color = Color::BLACK;
      return;
    }

    Node* s = n->sibling();
    if (s->color == Color::RED) {
      s->color = Color::BLACK;
      p->color = Color::RED;
      if (n->is_left()) {
        rotate_left(s);
      } else {
        rotate_right(s);
      }
      update_height(p);
    }

    s = n->sibling();
    if (p->color == Color::BLACK 
        && s->color == Color::BLACK 
        && s->left->color == Color::BLACK 
        && s->right->color == Color::BLACK) {
      s->color = Color::RED;
      erase_adjust(p);
    } else if (p->color == Color::RED
        && s->color == Color::BLACK 
        && s->left->color == Color::BLACK 
        && s->right->color == Color::BLACK) {
      p->color = Color::BLACK;
      s->color = Color::RED;
    } else {
      if (s->color == Color::BLACK) {
        if (n->is_left() && s->left->color == Color::RED && s->right->color == Color::BLACK) {
          s->color = Color::RED;
          s->left->color = Color::BLACK;
          rotate_right(s->left);
        } else if (n->is_right() && s->right->color == Color::RED && s->left->color == Color::BLACK){
          s->color = Color::RED;
          s->right->color = Color::BLACK;
          rotate_left(s->right);
        }
        update_height(s);
      }

      s = n->sibling();
      s->color = p->color;
      p->color = Color::BLACK;
      if (n->is_left()) {
        s->right->color = Color::BLACK;
        rotate_left(s);
      } else {
        s->left->color = Color::BLACK;
        rotate_right(s);
      }
      update_height(p);
    }
  }

  void update_height(Node* n) {
    while (!nil(n)) {
      n->height = nil(n) ? 0 : max(n->left->height, n->right->height) + 1;
      n = n->parent; 
    }
  }

  int rec_get_height(Node* n) {
    if (nil(n)) return 0;
    return 1 + max(rec_get_height(n->left), rec_get_height(n->right));
  } 

  Node* root = nullptr;
  Node* NIL = nullptr;
  size_t sz = 0;
};


// ------------------------------------- TEST -------------------------------------

vector<int> gen_test_input(int n) {
  vector<int> a(n, 0);
  for (int i=0;i<n;++i) {
    a[i] = i;
  }
  return a;
}

void shuffle(vector<int>& a) {
  std::random_device rd;
  std::mt19937 gen(rd());
  int n = a.size();
  for (int i=0;i<n;++i) {
    std::uniform_int_distribution<> distrib(i, n-1);
    int j = distrib(gen);
    swap(a[i], a[j]);
  }
}

void test_insert(int n) {
  vector<int> input = gen_test_input(n); 
  shuffle(input);

  RBTree<int> tree;
  set<int> contain;
  for (int i=0;i<n;++i) {
      int x = input[i];
      tree.insert(x);
      contain.insert(x);
      for (int j=0;j<n;++j) {
        auto node = tree.search(j);
        if (contain.count(j)) {
          assert(node != nullptr);
        } else {
          assert(node == nullptr);
        }
      }

    }
}

void test_erase(int n) {
  RBTree<int> tree;
  unordered_set<int> contain;
  for (int i=0;i<n;++i) {
    tree.insert(i);
    contain.insert(i);
  }

  vector<int> input = gen_test_input(n); 
  shuffle(input);
  for (int i=0;i<n;++i) {
    int x = input[i];
    // cout << "to_erase: " << x << endl;
    tree.erase(x);
    contain.erase(x);
    for (int j=0;j<n;++j) {
      auto node = tree.search(j);
      if (contain.count(j)) {
        assert(node != nullptr);
      } else {
        assert(node == nullptr);
      }
    }
  }
}

void test_insert_erase(int n) {
  vector<int> input = gen_test_input(2 * n);
  shuffle(input);

  RBTree<int> tree;
  unordered_set<int> contain;
  for (int i=0;i<2*n;++i) {
    int x = input[i] % n;
    if (!contain.count(x)) {
      tree.insert(x);
      contain.insert(x);
    } else {
      tree.erase(x);
      contain.erase(x);
    }
    for (int j=0;j<n;++j) {
      auto node = tree.search(j);
      if (contain.count(j)) {
        assert(node != nullptr);
      } else {
        assert(node == nullptr);
      }
    }
  }
}

void test(int n) {
  test_insert(n);
  test_erase(n);
  test_insert_erase(n);
}

int main() {
  int N = 100000;
  test(N);
}