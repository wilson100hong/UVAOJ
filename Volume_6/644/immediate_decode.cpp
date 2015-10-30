#include <iostream>
using namespace std;

struct Node {
  Node* child[2];
  bool terminal = false;
};

void release(Node* node) {
  if (node == nullptr) return;
  for (int i = 0; i < 2; ++i) {
    release(node->child[i]);
  }
  free(node);
}

// return true if the code can be added to tree and still immediate decodable. false otherwise
bool add(Node* node, const string& code) {
  if (node == nullptr) return false;  // should never happen
  if (node->terminal) return false;

  if (code.size() == 0) {
    node->terminal = true;
    if (node->child[0] != nullptr || node->child[1] != nullptr) {
      return false;
    } else {
      return true;
    }
  }
  
  int bit = code[0] - '0';
  if (bit < 0 || bit > 2) {
    return false;  // should never happen
  }

  if (node->child[bit] == nullptr) {
    node->child[bit] = new Node();
  }
  return add(node->child[bit], code.substr(1));
}

int main() {
  string line;
  Node* root = new Node();
  bool decodable = true;
  int round = 1;
  while (getline(cin, line)) {
    if (line[0] == '9') {
      if (decodable) {
        cout << "Set " << round << " is immediately decodable" << endl;
      } else {
        cout << "Set " << round << " is not immediately decodable" << endl;
      }
      release(root);
      root = new Node();
      decodable = true;
      round++;
    } else {
      decodable &= add(root, line);
    }
  }
}
