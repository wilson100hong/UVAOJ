#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <queue>

using namespace std;

class Node{
public:
  Node(string name_) {
    name = name_;
    parent = NULL;
  }
  Node* parent;
  vector<Node*> childs;
  string name;
  int level;
  int group;
};

void DumpTree(Node* root) {
  queue<Node*> q1;
  queue<Node*> q2;
  q1.push(root);
  while (!q1.empty() && q2.empty()) {
    while (!q1.empty()) {
      Node* node = q1.front();
      cout << node->name << ", " << node->group << "," << node->level << " ; ";
      q1.pop();
      
      for (int i = 0; i < node->childs.size(); ++i) 
        q2.push(node->childs[i]);
      cout << endl;
    }
    swap(q1, q2);
  }
  cout << "#########" << endl;
}


int main() {
  map<string, Node*> node_map;
  map<string, Node*>::iterator it;
  string parent_name, child_name;
  Node* parent_node, *child_node;
  vector<Node*> roots;
   
  // 1. Insert Nodes 
  while (cin >> child_name >> parent_name) {
    if (child_name == "no.child" &&
      parent_name == "no.parent") 
      break;
    // Create parent node if not exist
    if (node_map.find(parent_name) == node_map.end()) 
      node_map[parent_name] = new Node(parent_name);
    parent_node = node_map[parent_name];
    // Create child node if not exist
    if (node_map.find(child_name) == node_map.end()) 
      node_map[child_name] = new Node(child_name);
    child_node = node_map[child_name];
    // Link nodes
    child_node->parent = parent_node;
    parent_node->childs.push_back(child_node);
  }

  // 2. Assign level to each Nodes
  queue<Node*> node_queue;
  int group_index = 0;
  for (it = node_map.begin(); it != node_map.end(); ++it) {
    Node* node = it -> second;
    if (node -> parent == NULL) {
      node -> group = group_index++;
      node -> level = 0;
      roots.push_back(node);
      node_queue.push(node);
    }
  }

  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    node_queue.pop();
    for (int i = 0; i < node->childs.size(); ++i) {
      node->childs[i] -> group = node -> group;
      node->childs[i] -> level = node -> level + 1;
      node_queue.push(node->childs[i]);
    }
  }
 
  string p_name, q_name;
  Node *p_node, *q_node;
  while (cin >> p_name >> q_name) {
    if (node_map.find(p_name) == node_map.end() || node_map.find(q_name) == node_map.end()) {
      cout << "no relation" << endl;
      continue;
    }
    p_node = node_map[p_name];
    q_node = node_map[q_name];
    if (p_node == q_node) {
      cout << "sibling" << endl;
    } else if (p_node -> group != q_node -> group) {
      cout << "no relation" << endl;
    } else {
      int p2lca = 0, q2lca = 0;
      // TODO: Find least common ancestor
      while (p_node->level > q_node->level) {
        p_node = p_node -> parent;
        p2lca++;
      }
      while (q_node->level > p_node->level) {
        q_node = q_node -> parent;
        q2lca++;
      }
      
      while (p_node != q_node) {
        p_node = p_node -> parent; p2lca++;
        q_node = q_node -> parent; q2lca++;
      }

      //cout << p2lca << ", " << q2lca << endl;
      Node* lca = q_node;
      if (lca == node_map[p_name]) {
        // p is parent of q
        while (q2lca > 2) {
          q2lca--;
          cout << "great ";
        }
        if (q2lca > 1) {
          q2lca--;
          cout << "grand ";
        }
        cout << "parent" << endl;
      } else if (lca == node_map[q_name]) {
         // p is child of q
        while (p2lca > 2) {
          p2lca--;
          cout << "great ";
        }
        if (p2lca > 1) {
          p2lca--;
          cout << "grand ";
        }
        cout << "child" << endl;
      } else {
        int cousin = min(p2lca - 1, q2lca - 1);
        int removed = abs(p2lca - q2lca);
        if (cousin == 0 && removed == 0)
          cout << "sibling" << endl;
        else {
          cout << cousin << " cousin";
          if (removed > 0)
            cout << " removed " << removed;
          cout << endl;
        }
      }
    }
  }
}
