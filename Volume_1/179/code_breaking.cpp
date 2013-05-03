#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

bool RecBPM(int u,
  vector<bool>& seen, 
  const vector< set<int> >& graph, 
  vector<int>& r_match) {

   set<int>::iterator it;
   for (it = graph[u].begin(); it != graph[u].end(); ++it) {
      int v = *it;
      if (seen[v]) 
         continue;
      seen[v] = true;
      if (r_match[v] == -1 || RecBPM(r_match[v], seen, graph, r_match)) {
         r_match[v] = u;   
         return true;
      } 
   }
   return false;
}

int BPM(const vector<set<int> >& graph, vector<int>& r_match) {
   r_match.clear();
   for (int i = 0; i < graph.size(); ++i) 
      r_match.push_back(-1);

   int cnt = 0;
   for (int u = 0; u < graph.size(); ++u) {
      vector<bool> seen(graph.size(), false);
      if (RecBPM(u, seen, graph, r_match))
         cnt++;
   }
   return cnt;
}

string Padding(string s, int n) {
   stringstream ss;
   ss << s;
   for (int i = 0; i < n - s.length(); ++i)
      ss << "?";
   return ss.str();
}

void DumpGraph(const vector< set<int> >& graph) {
   for (int i = 0; i < graph.size(); ++i) {
      set<int>::iterator it;
      cout << i << ": ";
      for (it = graph[i].begin(); it != graph[i].end(); ++it) {
         cout << *it << ",";
      }
      cout << endl;
   }
}

void BuildGraph(string text, string cypher, int k, vector< set<int> >&graph) {
   graph.clear();
   // Add edges 
   for (int i = 0; i < k; ++i) {
      set<int> edges;
      for (int j = 0; j < k; ++j) {
         if (text[i] == cypher[j])
            edges.insert(j);
      }
      graph.push_back(edges);
   }
   
   // Remove invalid edges
   int len = text.length();
   for (int start = k; start < len; start += k) {
      for (int i = start; i < start + k; ++i) {
         int gi = i - start;
         for (int j = start; j < start + k; ++j) {
            int gj = j - start;
            if (text[i] != cypher[j]) {
               if (graph[gi].find(gj) != graph[gi].end()) {
                  graph[gi].erase(gj);
               }
            }
         }
      }
   }
}

int Hack(string text, string cypher, vector<int>& perm) {
   int tlen = text.length(), clen = cypher.length();
   if (tlen < clen)
      text = Padding(text, clen);
   vector< set<int> > graph;
   for (int k = 1; k <= clen; ++k) {
      if (clen % k != 0)   
         continue;
      BuildGraph(text, cypher, k, graph);
      if (k == BPM(graph, perm))
         return k;
   }
   return -1;
}

string Reorder(string s, const vector<int>& perm) {
   // Reorder with perm
   if (s.length() != perm.size())
      cout << "YOU IDIOT" << endl;
   stringstream ss;
   int len = s.length();
   for (int i = 0; i < len; ++i) {
      for (int j = 0; j < len; ++j)
         if (perm[j] == i) {
            ss << s[j];
            break;
         }
   }
   return ss.str();
}

string Decode(string s, const vector<int>& perm) {
   int k = perm.size(); // Period
   int len = s.length();
   int start = 0;
   string ret = "";
   while (start + k <= len) {
      string sub = s.substr(start, k);
      ret += Reorder(sub, perm);
      start += k;
   }
   // Rest stuff
   if (start < len) {
      string sub = Padding(s.substr(start, len - start), k);
      ret += Reorder(sub, perm);
   }
   return ret;
}

int main() {
   string text, cypher1, cypher2;
   while (getline(cin, text) && text != "#") {
      getline(cin, cypher1);
      getline(cin, cypher2);
      vector<int> perm;
      int k = Hack(text, cypher1, perm);
      if (k > 0) 
         cout << Decode(cypher2, perm) << endl; 
      else 
         cout << cypher2 << endl;
   }
}
