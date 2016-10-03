#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <set>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

struct Agent{
  string name;
  int a;
  int b;
};

Agent parse_line(const string& line) {
  int cur = 0;
  while (line[cur] != ':') {
    cur++;
  }
  string name = line.substr(0, cur);
  cur++; // skip ':'
  int a = 0;
  while (line[cur] != ',') {
    a = a*10 + (line[cur]-'0');
    cur++;
  }
  cur++;   // skip ','
  int b = 0;
  while (cur < line.size()) {
    b = b*10 + (line[cur]-'0');
    cur++;
  }
  return {name, a, b};
}

pair<int, string> quote(const Agent& agent, int loading, int target) {
  int cost = 0;

  while (loading > target) {
    // the cost if we try b
    int nl = loading/2;
    if (nl >= target && agent.b <= (loading-nl)*agent.a) {
      cost += agent.b;
      loading = nl;
    } else { cost += ((loading-target)*agent.a);
      loading = target;
    }
  }
  return {cost, agent.name};
}

void solve(const vector<Agent>& agents, int N, int M) {
  set<pair<int, string>> list;
  for (const Agent& agent : agents) {
    list.insert(quote(agent, N, M));
  }
  for (const auto& kv : list) {
    cout << kv.second << " " << kv.first << endl;
  }
}

int main() {
  int cases;
  string line;
  eatline() >> cases;
  for (int cs=1;cs<=cases;++cs) {
    int N, M, L;
    eatline() >> N >> M >> L; 
    vector<Agent> agents;
    for (int i=0;i<L;++i) {
      getline(cin, line);
      Agent agent = parse_line(line);
      agents.push_back(agent);
    }
    cout << "Case " << cs << endl;
    solve(agents, N, M);
  }
}
