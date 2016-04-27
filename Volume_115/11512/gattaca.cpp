#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

/*** Suffix Tree begin ***/
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
  cout << "active point node: " << point.node->label
       << ", edge: " << pc(point.edge)
       << ", offset: " << point.offset
       << endl;
}

// relocate active point when reaching edge's end
void relocate(STActivePoint& point) {
  STNode* child = point.node->edge[point.edge];
  if (child != nullptr) {
    if (child->start + point.offset >= child->end) {
      point = {child, 0, 0};
    }
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

    STNode* prev = nullptr;
    while (remainder > 0) {
      // whether the character exist in active point's sub-tree
      bool existed;
      if (point.offset == 0) {
        existed = point.node->edge[ch] != nullptr;
      } else {
          STNode* child = point.node->edge[point.edge];
          existed = list[child->start + point.offset] == ch;
      } 

      if (existed) {
        if (point.offset == 0) {
          point.edge = ch;
        }
        point.offset++;
        relocate(point);
        // prefix exist in current tree, either explicitly or implicitly, so no
        // need to insert.
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
        relocate(point);
      }
    }
  }

  // TEST
  //cout << "Result for str: " <<  str << endl;
  //dump_suffix_tree(list, root, 0, list.size() - 1, 0);
  //cout << endl;
  //dump_point(point);
  //cout << "-------------------------------------" << endl;
  return root;
}

void release_suffix_tree(STNode* node) {
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      release_suffix_tree(node->edge[i]);
    }
  }
  free(node);
}

/*** Suffix Tree end ***/

tuple<string, int> DFS(const string& str, const string& prev, STNode* node) {
  if (node->end == oo) {  // leaf
    return prev;
  }

  string current = prev;
  int pz = prev.size();
  int len = node->end - node->start;
  current.resize(pz + len);
  for (int i = 0; i < len; ++ i) {
    current[pz + i] = str[node->start + i];
  }

  int cnt = 0;
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      cnt++;
    }
  }
  string best = current;
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      string ts;
      int tc;
      tie(ts, tc) = DFS(str, current, node->edge[i]);
      if (ts.size() > best.size()) {
        best = ts;
        cnt = tc;
      }
    }
  }
  return make_tuple(best, cnt);
}

// need count
void Solve(const string& str) {
  STNode* root = build_suffix_tree(str);
  string sequence;
  int cnt;
  //tie(sequence, cnt) = DFS(str, "", root);
  release_suffix_tree(root);
  //if (cnt == 1 || sequence == "") {
    //cout << "No repetitions found!" << endl;
  //} else {
    //cout << sequence << " " << cnt << endl;
  //}
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    Solve(str);
  }
}
