#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <memory>
using namespace std;

typedef map<char, set<char>> Graph;

class Node {
 public:
  Node(char o_c) : c(o_c) {}
  ~Node() {
    for (Node* node : childs) {
      delete node;
    }
  }

  void UpdateGraph(Graph& graph) {
    if (c != '-' && !graph.count(c)) {
      graph[c] = set<char>();
    }
    for (int i=0;i<childs.size();++i) {
      for (int j=i+1;j<childs.size();++j) {
        char u = childs[i]->c, v = childs[j]->c;
        if (u != v) {
          graph[u].insert(v);
        }
      }
    }
    for (Node* node : childs) {
      node->UpdateGraph(graph);
    }
  }

  void Insert(const string& str) {
    if (str.empty()) return;
    char c = str[0];
    if (indices.count(c) == 0) {
      indices[c] = childs.size();
      childs.push_back(new Node(c));
    }
    childs[indices[c]]->Insert(str.substr(1));
  }

  void Dump(int level) {
    for (int i=0;i<level;++i) {
      cout << " ";
    }
    cout << c << endl;
    for (Node* node : childs) {
      node->Dump(level + 2);
    }
  }

  char c;
  vector<Node*> childs;
  map<char, int> indices;
};

class Trie {
 public:
  Trie() {
    root = new Node('-');  // Root is special char.
  }
  ~Trie() {
    delete root;
  }


  void Insert(const string& str) {
    root->Insert(str);
  }

  void UpdateGraph(Graph& graph) {
    root->UpdateGraph(graph);
  }

  void Dump() {
    root->Dump(0);
  }

  Node* root;
};

void DFS(Graph& graph, char u, set<char>& visited, vector<char>& posts) {
  visited.insert(u);
  for (char v : graph[u]) {
    if (!visited.count(v)) {
      DFS(graph, v, visited, posts);
    }
  }
  posts.push_back(u);
}

string Solve(Trie& trie) {
  Graph graph;
  trie.UpdateGraph(graph);

  // Topological sort
  set<char> visited;
  vector<char> posts;
  for (const auto& kv : graph) {
    char u = kv.first;
    if (!visited.count(u)) {
      DFS(graph, u, visited, posts);
    }
  }

  reverse(posts.begin(), posts.end());
  return string(posts.begin(), posts.end());
}

int main() {
  string line;

  Trie* trie = new Trie();
  while (getline(cin, line)) {
    if (line == "#") {
      cout << Solve(*trie) << endl;
      delete trie;
      trie = new Trie();
    } else {
      trie->Insert(line);
    }
  }
}
