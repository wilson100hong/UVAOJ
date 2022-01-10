// TODO: has bug, suffix link is wrong
// TODO: seg fault
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define oo 1000000
#define NULLCHAR '$'

vector<char> MakeCharList(const string& str) {
  vector<char> list;
  for (int i = 0; i < str.size(); ++i) {
    list.push_back(str[i]);
  }
  list.push_back(0);  // append '\0' at the end
  return list;
}

// print char: '\0' will be treat specially since it cannot be printed.
inline char pc(char c) { return c == 0 ? NULLCHAR : c; }
// cover letters from str[start] to str[end - 1]
class STNode {
  public:
    STNode(int start_, int end_, int label_)
        : start(start_), end(end_), label(label_) {
      for (int i = 0; i < 128; ++i) {
        edge[i] = nullptr;
      }
    }
    int len() {
      return end - start;
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

void DumpPoint(const STActivePoint& point) {
  cout << "active point node: " << point.node->label // << pc(list[point.node->start])
       << ", edge: " << pc(point.edge)  // static_cast<char>(point.edge)
       << ", offset: " << point.offset
       << endl;
}

// this will print "[3]: abcab$"
void DumpNode(const vector<char>& list, const STNode* node,
    int index, int remainder) {
  cout << "--node " << node->label<< ": ";
  //for (int i = node->start; i < node->end && i <= index - remainder; ++i) {
  for (int i = node->start; i < node->end && i <= index; ++i) {
    cout << pc(list[i]);
  }
  if (node->suffix != nullptr) {
    cout << " ~ suffix: " << node->suffix->label;
  }
  cout << endl;
}

void DumpSuffixTree(const vector<char>& list, const STNode* node,
    int depth, int index, int remainder) {
  int indent = depth;
  while (indent-- > 0) {
    cout << "  ";  // 2x spaces
  }
  DumpNode(list, node, index, remainder);
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      DumpSuffixTree(list, node->edge[i], depth + 1, index, remainder);
    }
  }
}

vector<string> GetAllSuffix(
    const vector<char>& list, const STNode* node, const string& prefix) {
  string s = prefix;
  if (node->end == oo) {
    for (int i = node->start; i < list.size(); ++i) {
      s += pc(list[i]);
    }
    return {s};
  } else {
    for (int i = node->start; i < node->end; ++i) {
      s += pc(list[i]);
    }
    vector<string> result;
    for (int i = 0; i < 128; ++i) {
      if (node->edge[i] != nullptr) {
        vector<string> tmp = GetAllSuffix(list, node->edge[i], s);
        for (const string& ts : tmp) {
          result.push_back(ts);
        }
      }
    }
    return result;
  }
}

void Validate(const vector<string>& all_suffix, const vector<char>& list) {
  set<string> all_suffix_set;
  for (const string& suffix : all_suffix) {
    all_suffix_set.insert(suffix);
  }
  string entire = "";
  for (int i = 0; i < list.size(); ++i) {
    entire += pc(list[i]);
  }
  for (int i = 0; i < list.size(); ++i) {
    string tmp = entire.substr(i);
    cout << "tmp: " << tmp << endl;
    if (all_suffix_set.count(tmp) == 0) {
      cout << "suffix: " << tmp << " missing." << endl;
    }
  }
}

// Advance active point if necessary.
void MaybeAdvance(
    const vector<char>& list, int index, STActivePoint& point) {
  while (1) {
    STNode* child = point.node->edge[point.edge];
    if (child == nullptr || child->start + point.offset < child->end) {
      return;
    }
    point.node = child;
    point.offset -= child->len();
    if (point.offset != 0) {
      // update active edge since we advance the active point.
      // for example,
      //   remaining : bcdef 
      //   index:    : 12345
      // current index = 5, after advance offset = 2
      // meaning that "ef" is the rest string that succeeding the new active node.
      // the active edge is the first char of the rest string, which is 'e',
      // which is list[5 - 2 + 1] = list[4]
      // TODO: wrong
      point.edge = list[index - point.offset];
      //point.edge = list[index - point.offset+ 1];
    } else {
      point.edge = 0;
    }
  }
}

// Whether prefix (starting at index - remainder - 1) exist in the tree
// this can be determined by check if ch is under current active node.
bool IsPrefixExist(const vector<char>& list, const STActivePoint& point, char ch) {
  if (point.offset == 0) {
    return point.node->edge[ch] != nullptr;
  } else {
    STNode* child = point.node->edge[point.edge];
    if (child == nullptr) {
      // TODO: this will happen..
cout << "WILSON IS STUPID" << endl;
    }
    return list[child->start + point.offset] == ch;
cout << "start: " << child->start << endl;
cout << "offset: " << point.offset << endl;
  } 
}

// Build suffix tree
STNode* BuildSuffixTree(const string& str) {
  vector<char> list = MakeCharList(str);

  int label = 0; 
  STNode* root = new STNode(0, 0, label++);
  STActivePoint point = {root, 0, 0};
  int remainder = 0;
  STNode* prev = nullptr;

  for (int index = 0; index < list.size(); ++index) {
    char ch = list[index];
cout << "===========================================" << endl;
cout << "round #" << index << " ch: " << ch << endl;

    if (remainder == 0) {
cout << "Clear prev" << endl;
      prev = nullptr;
    }
    remainder++;

    while (remainder > 0) {
      bool should_break = false;

      if (IsPrefixExist(list, point, ch)) {
        // prefix exist in current tree, either explicitly or implicitly, so no
        // need to insert.
        if (point.offset == 0) {
          point.edge = ch;
          // TODO: not sure
          if (point.node != root && prev != nullptr) {
            prev->suffix = point.node;
          }
        }
        // TODO: not sure, but looks correct
        prev = nullptr;

        point.offset++;
        // will update active point later

cout << "CASE #1" << endl;
DumpSuffixTree(list, root, 0, index, remainder);
cout << endl;
cout << "remainder:" << remainder << endl;
DumpPoint(point);
cout << endl;

        should_break = true;
      } else {
        STNode* added;
        bool split = (point.offset != 0);  // split or insert
        if (split) {
          // split STNode on active point 
          STNode* child = point.node->edge[point.edge];
          added = new STNode(child->start, child->start + point.offset, label++);
          added->edge[ch] = new STNode(index, oo, label++); 
          child->start = added->end;
          added->edge[list[added->end]] = child;
          point.node->edge[point.edge] = added;
        } else {
          // insert only happen at non-leaf node. 
          added = new STNode(index, oo, label++);
          point.node->edge[ch] = added;
        }

        remainder--;

        // Create suffix link only if previous node exist, and current added
        // node is a split.
        
        // TODO: situation is wrong
        if (prev != nullptr) {
          if (split) {
            prev->suffix = added;
          } else if (point.node != root) {
            // append
            prev->suffix = point.node;
          }
        }
        //if (prev != nullptr && (split || point.node != root)) {
          //prev->suffix = added;
        //}

        prev = added;

        // TODO: not sure
        // update active point
        if (point.node == root) {
          if (split) {
cout << "#a" << endl;
            int next_edge = remainder <= 1 ? 0 : list[index - remainder + 1];
            // TODO: not sure it make us loss some suffix links...
            prev = remainder <= 1 ? nullptr : prev;
if (prev == nullptr) cout << "clear prev here!" << endl;
            point = {root, next_edge, point.offset - 1};
          } else {  // append
cout << "#b" << endl;
            point = {root, ch, 0}; 
            prev = nullptr;
          }
        } else {  // internal node
          if (point.node->suffix != nullptr) {
cout << "#c" << endl;
            point = {point.node->suffix, point.edge, point.offset};
          } else if (split) {
cout << "#d" << endl;
            int next_edge = list[index - remainder + 1];
            // TODO: should we consider remainder == 0?
            // TODO: use root?
            point = {root, next_edge, point.offset};
          } else {  // append
cout << "#e" << endl;
            point = {root, ch, 0};
            prev = nullptr;
          }
        }

cout << "CASE #2" << endl;
DumpSuffixTree(list, root, 0, index, remainder);
cout << endl;
cout << "remainder:" << remainder << endl;
DumpPoint(point);
cout << endl;
      }

      // advance active point when current offset reach a node's end.
cout << "  update active point..." << endl;
cout << "  before : ";
DumpPoint(point);

      MaybeAdvance(list, index, point);

cout << "  after: ";
DumpPoint(point);
cout << "  prev: " << (prev ? prev->label : -1) << endl;

      if (should_break) break;
    }
  }

cout << "-------------------------------------" << endl;
cout << "Result for str: " <<  str << endl;
DumpSuffixTree(list, root, 0, list.size() - 1, 0);
cout << endl;
DumpPoint(point);
cout << "-------------------------------------" << endl;

  vector<string> suffixs = GetAllSuffix(list, root, "");
  cout << "all suffix: " << endl;
  for (const string& s : suffixs) {
    cout << s << endl;
  }
cout << "-------------------------------------" << endl;

cout << "Validation" << endl;
Validate(suffixs, list);

  return root;
}

void ReleaseSuffixTree(STNode* node) {
  for (int i = 0; i < 128; ++i) {
    if (node->edge[i] != nullptr) {
      ReleaseSuffixTree(node->edge[i]);
    }
  }
  free(node);
}

int main() {
  string str;
  cout << "Input string: " << endl;
  cin >> str;
  STNode* root = BuildSuffixTree(str);
}
