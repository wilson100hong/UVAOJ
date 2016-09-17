// for each language, create 26 nodes for it
#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

struct Node{
  int index;
  string lang;  // language
  unordered_map<int, int> edges;  // (node_index, cost)
};

// map (language, initial) to node index
typedef unordered_map<string, vector<int>> LangInitMap;

void maybe_add_language(
    const string& lang, 
    LangInitMap& mapping,
    vector<Node>& nodes) {
  if (mapping.count(lang) == 0) {
    mapping[lang] = vector<int>(26, -1);
    for (int i=0;i<26;++i) {
      int index = nodes.size();
      mapping[lang][i] = index;
      nodes.push_back({index, lang, unordered_map<int, int>()});
    }
  }
}

void add_word(
    const string& word,
    const string& lang1,
    const string& lang2,
    LangInitMap& mapping, 
    vector<Node>& nodes) {
  int cost = word.size();
  int ini = word[0] -'a';
  int to = mapping[lang2][ini];
  for (int i=0; i<26;++i) {
    if (i != ini) {
      int from = mapping[lang1][i];
      Node& node = nodes[from];
      if (!node.edges.count(to) || cost < node.edges[to]) {
        node.edges[to] = cost;
      }
    }
  }
}

typedef pair<int, int> II;

int solve(
    const LangInitMap& mapping,
    const vector<Node>& nodes, 
    int start,
    int end) {
  // Dijkstra
  vector<int> dists(nodes.size(), -1);
  dists[start] = 0;

  set<II> pq;
  pq.insert({0, start});  // start node

  while (!pq.empty()) {
    II top = *pq.begin();
    pq.erase(top);
    int cur = top.second;
    if (cur == end) break;

    for (const auto& kv : nodes[cur].edges) {
      int next = kv.first;
      int cost = top.first + kv.second;
      if (dists[next] == -1 || cost < dists[next]) {
        if (dists[next] != -1) {
          pq.erase({dists[next], next});
        }
        dists[next] = cost;
        pq.insert({cost, next});
      }
    }
  }
  return dists[end];
}


int main() {
  vector<Node> nodes;
  LangInitMap mapping;

  while (1) {
    int M;
    cin >> M; 
    if (M == 0) break;

    nodes.clear();
    mapping.clear();

    string start_lang, end_lang;
    cin >> start_lang >> end_lang;
    maybe_add_language(start_lang, mapping, nodes);
    maybe_add_language(end_lang, mapping, nodes);

    for (int m=0;m<M;++m) {
      string lang1, lang2, word;
      cin >> lang1 >> lang2 >> word;
      maybe_add_language(lang1, mapping, nodes);
      maybe_add_language(lang2, mapping, nodes);

      add_word(word, lang1, lang2, mapping, nodes);
      add_word(word, lang2, lang1, mapping, nodes);
    }

    // create start and end node
    int start = nodes.size();
    Node node = {start, "", unordered_map<int, int>()};
    nodes.push_back(node);
    for (int i=0;i<26;++i) {
      int to = mapping[start_lang][i];
      nodes[start].edges[to] = 0;
    }

    int end = nodes.size();
    node = {end, "", unordered_map<int, int>()};
    nodes.push_back(node);
    for (int i=0;i<26;++i) {
      int from = mapping[end_lang][i];
      nodes[from].edges[end] = 0;
    }
    
    int ans = solve(mapping, nodes, start, end);
    if (ans == -1) {
      cout << "impossivel" << endl;
    } else {
      cout << ans << endl;
    }
  }
}


