// TODO: there are still some cases can be simplified.
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define oo 1000000
#define CHAR_SIZE 128
#define TERM_CHAR '$'  // terminal char

// cover letters from str[start] to str[end - 1]
class STNode {
  public:
    STNode(const vector<char>& list_, int start_, int end_, int label_)
        : list(list_), start(start_), end(end_), label(label_) {}

    int Len() { return end - start; }
    set<string> GetChildStrings(const string& prefix) {
      string str = prefix;
      if (end == oo) {  // leaf
        str += string(list.begin() + start, list.end());
        return {str};
      } else {  // has child
        str += string(list.begin() + start, list.begin() + end);
        set<string> result;
        for (int i = 0; i < CHAR_SIZE; ++i) {
          if (edge[i] != nullptr) {
            set<string> tmp = edge[i]->GetChildStrings(str);
            for (const string& t : tmp) {
              result.insert(t);
            }
          }
        }
        return result;
      }
    }
    void Dump(int indent, int index) const {
      for (int i = 0; i < 2*indent; ++i) {
        cout << " ";  // 2x spaces
      }
      cout << "--node " << label << ": ";
      for (int i = start; i < end && i <= index; ++i) {
        cout << list[i];
      }
      if (suffix != nullptr) {
        cout << " ~ suffix: " << suffix->label;
      }
      cout << endl;
      for (int i = 0; i < 128; ++i) {
        if (edge[i] != nullptr) {
          edge[i]->Dump(indent + 1, index);
        }
      }
    }

    const vector<char>& list;
    int start;
    int end;
    int label;
    STNode* edge[CHAR_SIZE] = { nullptr };
    STNode* suffix = nullptr;  // suffix link
};

class STActivePoint {
  public:
    STActivePoint() {}
    void Set(STNode* node_, int edge_, int offset_) {
      node = node_; edge = edge_; offset = offset_;
    }

    void Dump() const {
      if (node == nullptr) return;
      cout << "ActivePoint node: " << node->label
           << ", edge: " << edge
           << ", offset: " << offset
           << endl;
    }

    STNode* node;
    int edge;
    int offset;
};

class SuffixTree {
  public:
    SuffixTree(const string& str_) : str(str_) {
      list = vector<char>(str.begin(), str.end());
      list.push_back(TERM_CHAR);
      Build();
    }

    virtual ~SuffixTree() {
      if (root != nullptr) {
        ReleaseSTNode(root);
      }
    }
    void ReleaseSTNode(STNode* node) {
      for (int i = 0; i < CHAR_SIZE; ++i) {
        if (node->edge[i] != nullptr) {
          ReleaseSTNode(node->edge[i]);
        }
      }
      free(node);
    }

    // Whether prefix [index-remainder-1:index+1]  exist in the tree
    // this can be determined by check if ch is under current active node.
    bool IsPrefixExist(char ch) {
      if (point.offset == 0) {
        return point.node->edge[ch] != nullptr;
      } else {
        STNode* child = point.node->edge[point.edge];
        return list[child->start + point.offset] == ch;
      } 
    }

    // Advance active point if necessary.
    void MaybeAdvancePoint() {
      while (1) {
        STNode* child = point.node->edge[point.edge];
        if (child == nullptr || child->start + point.offset < child->end) {
          return;
        }
        point.node = child;
        point.offset -= child->Len();
        if (point.offset != 0) {
          point.edge = list[index - point.offset];
        } else {
          point.edge = 0;
        }
      }
    }

    void Build() {
      int label = 0; 
      root = new STNode(list, 0, 0, label++);
      point.Set(root, 0, 0);
      int remainder = 0;
      STNode* prev = nullptr;

      for (index = 0; index < list.size(); ++index) {
        char ch = list[index];
        if (remainder == 0) {
          prev = nullptr;
        }
        remainder++;

        while (remainder > 0) {
          bool should_break = false;
          if (IsPrefixExist(ch)) {
            // prefix exist in current tree, either explicitly or implicitly, so no
            // need to insert.
            if (point.offset == 0) {
              point.edge = ch;
              if (point.node != root && prev != nullptr) {
                prev->suffix = point.node;
              }
            }
            prev = nullptr;

            point.offset++;
            // will update active point later
            should_break = true;
          } else {
            STNode* added;
            bool split = (point.offset != 0);  // split or insert
            if (split) {
              // split STNode on active point 
              STNode* child = point.node->edge[point.edge];
              added = new STNode(list, child->start, child->start + point.offset, label++);
              added->edge[ch] = new STNode(list, index, oo, label++); 
              child->start = added->end;
              added->edge[list[added->end]] = child;
              point.node->edge[point.edge] = added;
            } else {
              // insert only happen at non-leaf node. 
              added = new STNode(list, index, oo, label++);
              point.node->edge[ch] = added;
            }

            remainder--;

            // Create suffix link only if previous node exist, and current added
            // node is a split.

            if (prev != nullptr) {
              if (split) {
                prev->suffix = added;
              } else if (point.node != root) {  // append at internal node
                prev->suffix = point.node;
              }
            }

            prev = added;

            // TODO: simplify further!
            // update active point
            if (point.node == root) {
              if (split) {
                int next_edge = remainder <= 1 ? 0 : list[index - remainder + 1];
                prev = remainder <= 1 ? nullptr : prev;
                point.Set(root, next_edge, point.offset - 1);
              } else {  // append
                point.Set(root, ch, 0); 
                prev = nullptr;
              }
            } else {  // internal node
              if (point.node->suffix != nullptr) {
                point.Set(point.node->suffix, point.edge, point.offset);
              } else if (split) {
                int next_edge = list[index - remainder + 1];
                point.Set(root, next_edge, point.offset);
              } else {  // append
                point.Set(root, ch, 0);
                prev = nullptr;
              }
            }
          }
          MaybeAdvancePoint();
          if (should_break) break;
        }
      }
    }

    set<string> GetAllSuffix() {
      if (root == nullptr) return {};
      return root->GetChildStrings("");
    }

    void Dump() const {
      if (root == nullptr) return;
      root->Dump(0, list.size() - 1);
    }

    string str;  // original string
    vector<char> list;
    int index = -1;
    STActivePoint point;
    STNode* root = nullptr;
};

void ValidateSuffixStrings(const set<string>& all_suffix, const vector<char>& list) {
  string entire(list.begin(), list.end());
  for (int i = 0; i < list.size(); ++i) {
    string tmp = entire.substr(i);
    if (all_suffix.count(tmp) == 0) {
      cout << "suffix: " << tmp << " missing." << endl;
    }
  }
}

int main() {
  string str;
  cout << "Input string: " << endl;
  cin >> str;
  SuffixTree st(str);
  set<string> suffix = st.GetAllSuffix();
  cout << "------" << endl;
  ValidateSuffixStrings(suffix, st.list);
}
