#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define LS 26 // letter size
using namespace std;

class Node{
public:
  Node() {
    value = 0;
    visited = false;
    pre = -1;
    post = -1;
    row = -1;
    col = -1;
  }

  int value;
  vector<Node*> childs;
  bool visited;
  int pre, post;
  int row, col;
};

char int2char(int n) {
  return (char) (n + 'A');
}
// Col start from 0
string GetCellColKey(int col) {
  int pow = LS;
  int s = 0;
  int digit = 1;
  while (s + pow <= col) {
    s += pow;
    pow *= LS;
    digit++;
  }
  col -= s;
  string ret = "";
  while (digit-- > 0) {
    ret = int2char(col % LS) + ret;
    col /= LS;
  }
  return ret;
}
// Row, Col start from 1
string GetCellKey(int row, int col) {
  stringstream ss;
  ss << GetCellColKey(col) << row + 1;
  return ss.str();
}

// the number is the next available when DFS is done
void DFS(Node* node, int& number) {
  node->visited = true;
  node->pre = number++;
  for (int i = 0;i < node->childs.size(); ++i) {
    Node* child = node->childs[i];
    if (!child->visited) 
      DFS(child, number);
  }
  node->post = number++;
}

// Put bigger post in front
int CompareNodePost(Node* node1, Node* node2) {
  if (node1 == NULL || node2 == NULL)
    cout << "YOU DUMB" << endl; 
  return node1->post > node2 -> post;
}

int CompaureNodeRowCol(Node* node1, Node* node2) {
  if (node1 == NULL || node2 == NULL)
    cout << "YOU DUMB" << endl; 
  if (node1->row == node2->row)
    return node1->col < node2->col;
  else
    return node1->row < node2->row;
}
void TS(vector<Node*>& node_list) {
  int number = 0;
  for (int i = 0; i < node_list.size(); ++i) 
    if (!node_list[i]->visited) 
      DFS(node_list[i], number);
  sort(node_list.begin(), node_list.end(), CompareNodePost);
}

int main() {
  int N;
  cin >> N;
  int col, row;
  string token;
  map<string, Node*> node_map;
  vector<Node*> node_list;
  
  while (N-- > 0) {
    cin >> col >> row;
    // 1. Read input, construct nodes
    for (int r = 0; r < row; ++r) {
      for (int c = 0; c < col; ++c) {
        string cell_key = GetCellKey(r, c);
        if (node_map.find(cell_key) == node_map.end()) {
          node_map[cell_key] = new Node();
          node_list.push_back(node_map[cell_key]);
        }
        Node* node = node_map[cell_key];
        node->row = r; node->col = c;
        cin >> token;
        if (token[0] == '=') {
          // TODO: parse formula
          // for each src, if not exist, create them
          token = token.substr(1, token.length() - 1);
          stringstream ss(token);
          string src_key;
          while (getline(ss, src_key, '+')) {
            if (node_map.find(src_key) == node_map.end()) {
              node_map[src_key] = new Node();
              node_list.push_back(node_map[src_key]);
            }
            Node* src = node_map[src_key];
            src->childs.push_back(node);
          }
          // add childs
        } else {
          stringstream ss(token);
          ss >> node->value;
        }
      }
    }

    // 2. Topological 
    TS(node_list);

    // 3. Iterate node_list and compute number
    for (int i = 0; i < node_list.size(); ++i) {
      Node* node = node_list[i];
      for (int j = 0; j < node->childs.size(); ++j)
        node->childs[j]->value += node->value;
    }

    // 4. Sort node_list in row column order, dump it
    sort(node_list.begin(), node_list.end(), CompaureNodeRowCol);
    int index = 0;
    for (int i = 0; i < node_list.size(); ++i) {
      if (i % col != 0)
        cout << " ";
      cout << node_list[i]->value;
      if (i % col == col - 1)
        cout << endl;
    }
    for (int i = 0; i < node_list.size(); ++i)
      delete node_list[i];
    node_list.clear();
    node_map.clear();
  }
}
