/**
 *  This problem is a standard graph problem testing of SCC:
 *  Strongly Connected Components algorithm. Just carefully group them,
 *  check every SCC (cycles) you found is purely async or not.
 *
 *  Then, use TP (Topological Sort) and DP to compute max delay for each
 *  async device. Notice that Sync device has no dely.
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Node{
   char type;
   int delay;
   vector<int> to;
   bool visit;
   int pre;
   int post;
   int group;
   int sum; // sum of delays
};

int DfsPrePost(vector<Node>& g, int u, int cnt) {
   g[u].visit = true;
   g[u].pre = cnt++;
   for (int i = 0; i < g[u].to.size(); ++i) {
      int v = g[u].to[i];
      if (!g[v].visit) 
         cnt = DfsPrePost(g, v, cnt);
   }
   g[u].post = cnt++;
   return cnt;
}

void DfsGroup(vector<Node>& g, int u, int group) {
   g[u].visit = true;
   g[u].group = group;
   for (int i = 0; i < g[u].to.size(); ++i) {
      int v = g[u].to[i];
      if (!g[v].visit) 
         DfsGroup(g, v, group);
   }
}

struct Stone{
   int index;
   int value;
};

inline int CompareStoneAsc(const Stone& s1, const Stone& s2) {
   return s1.value < s2.value;
}
inline int CompareStoneDesc(const Stone& s1, const Stone& s2) {
   return s1.value > s2.value; 
}

int main() {
   int round;
   cin >> round;
   vector<Node> graph;
   vector<Node> rev_graph;
   vector<Stone> stones;
   while (round -- > 0) {
      graph.clear();
      rev_graph.clear();
      stones.clear();
      int period, n, m;  // n: # of nodes, m: # of edges
      cin >> period >> n;
      // 1. build nodes: sync and async
      for (int i = 0; i < n; ++i) {
         Node node;
         node.sum = 0;
         node.visit = false;
         node.pre = -1;
         node.post = -1;
         node.group = -1;
         cin >> node.type >> node.delay; 
         graph.push_back(node);
         rev_graph.push_back(node);
      }
      // 2. build edges
      cin >> m;
      for (int i = 0; i < m; ++i) {
         int u, v;
         cin >> u >> v;
         graph[u].to.push_back(v);
         rev_graph[v].to.push_back(u);
      }
     
      // 3. SCC (strongest connected component)
      // a. DFS on rev_graph
      int cnt = 0;
      for (int i = 0; i < rev_graph.size(); ++i) {
         if (!rev_graph[i].visit) 
            cnt = DfsPrePost(rev_graph, i, cnt);
      }

      // b. sort rev_graph on post, higher preceed
      stones.clear();
      for (int i = 0; i < rev_graph.size(); ++i) {
         Stone stone = {i, rev_graph[i].post};
         stones.push_back(stone);
      }
      sort(stones.begin(), stones.end(), CompareStoneDesc);

      // c. grouping on graph (not rev_graph!)
      int gg = 0;
      // post large to small
      for (int i = 0; i < stones.size(); ++i) { 
         int index = stones[i].index;
         if (!graph[index].visit) {
            DfsGroup(graph, index, gg);
            gg++;
         }
      }

      // 4. check cycle
      stones.clear();
      for (int i = 0; i < graph.size(); ++i) {
         Stone stone = {i, graph[i].group};
         stones.push_back(stone);
      }

      sort(stones.begin(), stones.end(), CompareStoneAsc);

      bool cycle = false;
      int cur = 0;

      while (cur < n) {
         Node& node = graph[stones[cur].index];
         int group = node.group;
         int async = node.type == 'a';

         int next = cur + 1;
         while (next < n && graph[stones[next].index].group == group) {
            async &= (graph[stones[next].index].type == 'a');
            next++;
         }
         if (next - cur > 1 && async) {
            cycle = true;
            break;
         }
         cur = next;
      }

      if (cycle) {
         cout << "Circuit contains cycle." << endl;
      } else {
         // 5. TP calculate delay
         for (int i = 0; i < graph.size(); ++i)
            graph[i].visit = false;
         int cnt = 0;
         for (int i = 0; i < graph.size(); ++i) {
            if (!graph[i].visit) 
               cnt = DfsPrePost(graph, i, cnt);
         }

         stones.clear();
         for (int i = 0; i < graph.size(); ++i) {
            Stone stone = {i, graph[i].post};
            stones.push_back(stone);
         }
         sort(stones.begin(), stones.end(), CompareStoneDesc);

         for (int i = 0; i < graph.size(); ++i) {
            int u = stones[i].index;
            Node& node = graph[u];
            for (int j = 0; j < node.to.size(); ++j) {
               int v = node.to[j];
               Node& next = graph[v];
               if (next.type == 'a') {
                  int sum = node.sum + next.delay;
                  if (sum > next.sum) {
                     next.sum = sum;
                  }
               }
            }
         }

         // 6. max delay exceed?
         stones.clear();
         for (int i = 0; i < graph.size(); ++i) {
            Stone stone = {i, graph[i].sum};
            stones.push_back(stone);
         }
         sort(stones.begin(), stones.end(), CompareStoneDesc);

         int max_sum = stones[0].value;
         if (max_sum > period)
            cout << "Clock period exceeded." << endl;
         else
            cout << "Synchronous design. Maximum delay: " << max_sum << "." << endl;
      }
   }
}
