#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

stringstream SS;
stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

struct Team {
  int index;
  set<int> solved;  // problems solved
  map<int, int> failed;  // problem - falied count

  int ac = 0;
  int penalty = 0;
};

int compare_team(const Team& t1, const Team& t2) {
  if (t1.ac != t2.ac) {
    return t1.ac > t2.ac;
  }
  if (t1.penalty != t2.penalty) {
    return t1.penalty < t2.penalty;
  }
  return t1.index < t2.index;
}

int main() {
  int cases;
  eatline() >> cases;
  eatline();  // first blank line
  bool first = true;
  string line;
  while (cases--) {
    map<int, Team> teams;
    while (getline(cin, line)) {
      if (line == "") {
        break;
      }
      stringstream ss(line);
      int a, b, c;
      string s;
      ss >> a >> b >> c >> s;
      if (teams.count(a) == 0) {
        Team team;
        team.index = a;
        teams[a] = team; 
      }
      if (s == "R" || s == "U" || s == "E") {
        continue;
      }
      if (s == "I") {
        if (teams[a].solved.count(b)) {
          // TODO: not sure
          continue;
        }
        if (teams[a].failed.count(b) == 0) {
          teams[a].failed[b] = 0;
        }
        teams[a].failed[b]++;
      } else if (s == "C") {
        if (teams[a].solved.count(b)) {
          // TODO: not sure
          continue;
        }
        teams[a].solved.insert(b);
        teams[a].ac++;
        int failures = (teams[a].failed.count(b) ?
                        teams[a].failed[b] : 0);

        teams[a].penalty += (c + 20*failures);
      }
    }
    
    vector<Team> team_list;
    for (const auto& kv : teams) {
      team_list.push_back(kv.second);
    }

    sort(team_list.begin(), team_list.end(), compare_team);

    if (!first) {
      cout << endl;
    }
    for (const Team& team : team_list) {
      cout << team.index << " " << team.ac << " " << team.penalty << endl;
    }

    first = false;
  }
}
