#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;
class Node {
public:
  int value;
  string pos; // "LLR)" 
  Node(int v_, string pos_) {
    value = v_; pos = pos_;
  }
};


bool compLR(char c1, char c2) {
   return c1 < c2; // 'L' < 'R'
}

bool mycomp(const Node& n1, const Node& n2) {
  string pos1 = n1.pos, pos2 = n2.pos;
  if (pos1.length() != pos2.length()) {
    return pos1.length() < pos2.length();
  } else {
    int len = pos1.length();
    for (int i = 0; i < len - 1; ++i) {
      if (pos1[i] != pos2[i]) {
        return compLR(pos1[i], pos2[i]);      
      }
    }
  }
  return true; // whatever
}

int main () {
  vector<Node> tree;
  string input;
  while(cin >> input) {
    if (input == "()") {
      // 1. sort
      sort(tree.begin(), tree.end(), mycomp);
      // 2. complete?
      bool complete = true;
      for (int i = tree.size() - 1; i >= 0; --i) {
        string pos = tree[i].pos;
        //cout << pos << endl;
        if (pos.length() > 1) { // not root
          int len_pos = pos.length();
          string parent_pos = pos.substr(0, len_pos - 2);
          parent_pos = parent_pos + ")";
          bool findParent = false;
          for (int j = tree.size() - 1; j >= 0; --j) {
            if (j != i && tree[j].pos == parent_pos) {
              findParent = true;
              break;
            }
          }
          if (findParent == false) {
            complete = false;
            break;
          }
        }
      }

      if (complete) {
        for (int i = 0; i < tree.size() - 1; ++i) {
          if (tree[i].pos == tree[i+1].pos) {
            complete = false;
            break; 
          }
        }
      }

      if (!complete) 
        cout << "not complete";
      else {
        cout << tree[0].value;
        for (int i = 1; i < tree.size(); ++i)
          cout << " " << tree[i].value;
      }
      cout << endl;
      tree.clear();
    } else {
      // parse input
      stringstream ss(input);
      char c;
      ss >> c; // '('
      int value;
      ss >> value;
      ss >> c; // ','
      string pos;
      ss >> pos; // "LLR)"
      //cout << pos << endl;
      Node node(value, pos);
      tree.push_back(node);
    }
  }
}
