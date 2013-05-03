#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  int value;
  Node* left;
  Node* right;
  Node(int value_) {
    value = value_;
    left = NULL;
    right = NULL;
  }
};

void recSum(const Node* node, vector<int>& sums, const int accum) {
  if (node == NULL)
    return;
  
  if (node->left == NULL && node->right == NULL) {
    sums.push_back(accum + node->value);
    return;
  }
  if (node->left != NULL)
    recSum(node->left, sums, accum + node->value);
  if (node->right != NULL) 
    recSum(node->right, sums, accum + node->value);
}
void buildSums(const Node* tree, vector<int>& sums) {
  sums.clear();
  recSum(tree, sums, 0);
}

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

bool isLeftParen(char c) {
  return c == '(';
}

bool isRightParen(char c) {
  return c == ')';
}

int charToInt(char c) {
  return (int) c - '0';
}

Node* buildTree(bool needLeft) {
  char c;
  if (needLeft) {
    // skip space or other stuffs until meet '('
    while (cin >> c) {
      if (isLeftParen(c))
        break;
    }
  }
  while (cin >> c) {
    if (isRightParen(c)) {
      return NULL;
    } else if (c == '-' || isDigit(c)) {
      int v = 0;
      int neg = 1;
      
      if (c == '-')
        neg = -1;
      else 
        v = charToInt(c);
      
      while(cin >> c) {
        if (isDigit(c)) {
          v = v*10 + charToInt(c);
        } else {
          break;
        }
      }
      v *= neg;
      //  cout << "create node: " << v << endl;
      Node* node = new Node(v);
      bool needLeft = (c != '('); 
      
      Node* left = buildTree(needLeft);
      Node* right = buildTree(true);
      
      node->left = left;
      node->right = right;
      while (cin >> c) {
        if (isRightParen(c)) {
          break;
        }
      }
      return node;
    }
    // else, skip this char
  }
//  cout << "format error" << endl;
  return NULL;
}


int main () {
  int target;
  vector<int> sums;
  while (cin >> target) {
    //cout << target << endl;
    
    Node* tree = buildTree(true);
    //cout << "tree done" << endl;
    
    buildSums(tree, sums);
    
    
    bool yes = false;
    for (int i = 0; i < sums.size(); ++i) {
      if (sums[i] == target) {
        yes = true;
        break; 
      }
    }
    cout << (yes ? "yes" : "no") << endl;
  }
  return 0;
}
