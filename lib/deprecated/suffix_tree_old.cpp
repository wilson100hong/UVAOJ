#include <iostream>
#include <vector>
using namespace std;

#define oo 1000000
#define NULLCHAR '$'

// cover letters from str[start] to str[end - 1]
class STNode {
  public:
    STNode(int start_, int end_, int label_)
        : start(start_), end(end_), label(label_) {
      for (int i = 0; i < 128; ++i) {
        edge[i] = nullptr;
      }
    }
    int start;
    int end;
    int label;
    STNode* edge[128];
    STNode* suffix = nullptr;  // suffix link
};

struct STActivePoint {
  STNode* node;
  int edge;
  int offset;
};

vector<char> make_char_list(const string& str) {
  vector<char> list;
  for (int i = 0; i < str.size(); ++i) {
    list.push_back(str[i]);
  }
  list.push_back(0);  // append '\0' at the end
  return list;
}

// print char: '\0' will be treat specially since it cannot be printed.
inline char pc(char c) { return c == 0 ? NULLCHAR : c; }

// this will print "[3]: abcab$"
void dump_node(const vector<char>& list, const STNode* node,
    int index, int remainder) {
  cout << "--node " << node->label<< ": ";
  for (int i = node->start; i < node->end && i <= index - remainder; ++i) {
    cout << pc(list[i]);
  }
  if (node->suffix != nullptr) {
    cout << " ~ suffix: " << node->suffix->label;
  }
  cout << endl;
}

void dump_suffix_tree(const vector<char>& list, STNode* node, int depth,
    int index, int remainder) {
  int indent = depth;
  while (indent-- > 0) {
    cout << "  ";  // 2x spaces
  }
  dump_node(list, node, index, remainder);
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      dump_suffix_tree(list, node->edge[i], depth + 1, index, remainder);
    }
  }
}

void dump_point(const STActivePoint& point) {
  cout << "active point node: " << point.node->label // << pc(list[point.node->start])
       << ", edge: " << pc(point.edge)  // static_cast<char>(point.edge)
       << ", offset: " << point.offset
       << endl;
}

// advance active node.
void advance(STActivePoint& point) {
  cout << "ADV" << endl;
  dump_point(point);
  STNode* child = point.node->edge[point.edge];
  cout << "cs: " << child->start << endl;
  cout << "ce: " << child->end << endl;
  // TODO: BUG
  //
  //if (child != nullptr) {
    //if (point.node->end == 0) {
      //if (child->start + point.offset >= child->end) {
        //point = {child, 0, 0};
      //}
    //} else {
      //if (point.node->end + point.offset >= child->end) {
        //point = {child, 0, 0};
      //}
    //}
  //}

  if (child != nullptr &&  // has child, and reach the end of current node's edge
      point.node->end + point.offset >= child->end) {
    point = {child, 0, 0};
  }
}

// Build suffix tree
STNode* build_suffix_tree(const string& str) {
  vector<char> list = make_char_list(str);

  int label = 0; 
  STNode* root = new STNode(0, 0, label++);
  STActivePoint point = {root, 0, 0};
  int remainder = 0;

  for (int index = 0; index < list.size(); ++index) {

    remainder++;
    char ch = list[index];
    cout << "round #" << index << endl;
    cout << "ch: " << ch << endl;

    STNode* prev = nullptr;
    while (remainder > 0) {
      // whether the character exist in active point's sub-tree
      bool existed;
      if (point.offset == 0) {
        existed = point.node->edge[ch] != nullptr;
      } else {
          STNode* child = point.node->edge[point.edge];
          if (child == nullptr) { cout << "WILSON IS STUPID" << endl;}  // should not happen
          //cout << "start: " << point.node->start << endl;
          //cout << "offset: " << point.offset << endl;
          existed = list[child->start + point.offset] == ch;
      } 

      if (existed) {
        if (point.offset == 0) {
          point.edge = ch;
        }
        point.offset++;
        advance(point);
        // prefix exist in current tree, either explicitly or implicitly, so no
        // need to insert.

  cout << "CASE 1" << endl;
  dump_suffix_tree(list, root, 0, index, remainder);
  cout << endl;
  cout << "remainder:" << remainder << endl;
  dump_point(point);
  cout << "-------------------------------------" << endl;
        break;
      } else {
        STNode* inserted;
        bool split = (point.offset != 0);  // split or append
        if (split) {
          // split STNode on active point 
          STNode* child = point.node->edge[point.edge];
          inserted = new STNode(child->start, child->start + point.offset, label++);
          inserted->edge[ch] = new STNode(index, oo, label++); 
          child->start = inserted->end;
          inserted->edge[list[inserted->end]] = child;
          point.node->edge[point.edge] = inserted;
        } else {
          // append STNode as child of active node
          inserted = new STNode(index, oo, label++);
          point.node->edge[ch] = inserted;
        }

        remainder--;

        // update suffix link only if split
        if (prev != nullptr && split) {
          prev->suffix = inserted;
        }
        prev = inserted;

        // update active point
        if (point.node == root) {
          if (split) {
            //int next_edge = list[root->edge[point.edge]->start + 1];
            int next_edge = list[index - remainder + 1];
            point = {root, next_edge, point.offset - 1};
          } else {  // append
            point = {root, ch, 0}; 
          }
        } else {  // internal nodes
          if (point.node->suffix != nullptr) {
            point = {point.node->suffix, point.edge, point.offset};
          } else if (split) {
            int next_edge = list[index - remainder + 1];
            point = {root, next_edge, point.offset};
          } else {  // append
            point = {root, ch, 0};
          }
        }

  cout << "CASE 2" << endl;
  dump_suffix_tree(list, root, 0, index, remainder);
  cout << endl;
  cout << "remainder:" << remainder << endl;
  dump_point(point);
  cout << "-------------------------------------" << endl;
      }
    }
  }

  // TEST
  cout << "Result for str: " <<  str << endl;
  dump_suffix_tree(list, root, 0, list.size() - 1, 0);
  cout << endl;
  dump_point(point);
  cout << "-------------------------------------" << endl;
  return root;
}

int main() {
  vector<string> inputs = {
    //"aaa", 
    //"aba", 
    //"abc", 
    //"abab", 
    //"abca", 
    //"abcab", 
    //"abcac", 
    //"abcabc", 
    //"abcabx", 
    //"abcabxa", 
    //"abcabxab", 
    //"abcabxabc", 
    //"abcabxaby", 
    //"abcabxabcd", 
    //"badd",
    //"badda",
    //"baddac",
    "baddaca",  // TODO: has empty node?
    //"cdddcdc"
  };

  string str;
  for (const string& str : inputs) {
    STNode* root = build_suffix_tree(str);
  }
}
