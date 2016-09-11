#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct Team {
  string name;
  int points = 0;
  int wins = 0;
  int ties = 0;
  int loses = 0;
  int goal_scored = 0;
  int goal_against = 0;
};

stringstream SS;

stringstream& eatline() {
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

int s2i(const string& s) {
  int result = 0;
  for (int i=0; i<s.size(); ++i) {
    result = result*10 + (s[i] - '0');
  }
  return result;
}

void parse_game(const string& line, map<string, Team>& teams) {
  // team_name_1#goals1@goals2#team_name_2
  int cur = 0;
  int last = cur;
  while (cur < line.size() && line[cur] != '#') {
    cur++;
  }
  string name1 = line.substr(last, cur-last);

  cur++; last = cur;
  while (cur < line.size() && line[cur] != '@') {
    cur++;
  }
  int goal1 = s2i(line.substr(last, cur-last));

  cur++; last = cur;
  while (cur < line.size() && line[cur] != '#') {
    cur++;
  }
  int goal2 = s2i(line.substr(last, cur-last));

  cur++; last = cur;
  while (cur < line.size()) {
    cur++;
  }
  string name2 = line.substr(last, cur-last);

  Team& team1 = teams[name1];
  Team& team2 = teams[name2];
  if (goal1 > goal2) {
    team1.wins++;
    team1.points += 3;
    team2.loses++;
  } else if (goal1 < goal2) {
    team1.loses++;
    team2.wins++;
    team2.points += 3;
  } else {
    team1.ties++;
    team1.points++;
    team2.ties++;
    team2.points++;
  }
  team1.goal_scored += goal1;
  team1.goal_against += goal2;
  team2.goal_scored += goal2;
  team2.goal_against += goal1;
}

string lower(const string& s) {
  string r = s;
  for (int i=0; i<r.size(); ++i) {
    if ('A' <= r[i] && r[i] <= 'Z') {
      r[i] = r[i] - 'A' + 'a';
    }
  }
  return r;
}

bool compare_team(const Team& t1, const Team& t2) {
  if (t1.points != t2.points) {
    return t1.points > t2.points;
  }
  if (t1.wins != t2.wins) {
    return t1.wins > t2.wins;
  }
  int d1 = t1.goal_scored - t1.goal_against;
  int d2 = t2.goal_scored - t2.goal_against;
  if (d1 != d2) {
    return d1 > d2;
  }
  if (t1.goal_scored != t2.goal_scored) {
    return t1.goal_scored > t2.goal_scored;
  }
  int g1 = t1.wins + t1.ties + t1.loses;
  int g2 = t2.wins + t2.ties + t2.loses;
  if (g1 != g2) {
    return g1 < g2;
  }
  string k1 = lower(t1.name);
  string k2 = lower(t2.name);
  return k1 < k2;
}

int main() {
  int cases;
  eatline() >> cases;
  bool first = true;
  map<string, Team> teams;  // name -> Team
  while (cases--) {
    teams.clear();
    string tournament;
    if (!first)  cout << endl;
    getline(cin, tournament);
    cout << tournament << endl;;
    int n;
    eatline() >> n;
    for (int i=0; i<n; ++i) {
      string name;
      getline(cin, name); 
      Team team;
      team.name = name;
      teams[team.name] = team;
    }
    int g;
    eatline() >> g;
    for (int i=0; i<g; ++i) {
      string game;
      getline(cin, game);
      parse_game(game, teams);
    }

    // TODO: optmize if too slow
    vector<Team> team_list;
    for (const auto& kv : teams) {
      //team_list.push_back(&(kv.second));
      team_list.push_back(kv.second);
    }

    sort(team_list.begin(), team_list.end(), compare_team);
    
    for (int i=1; i<= team_list.size(); ++i) {
      const Team& team = team_list[i-1];
      cout << i << ") " << team.name << " " << team.points << "p, "
        << (team.wins + team.loses + team.ties) << "g ("
        << team.wins << "-" << team.ties << "-" << team.loses
        << "), " << (team.goal_scored - team.goal_against) << "gd (" << team.goal_scored << "-"
        << team.goal_against << ")" << endl;
    }

    first = false;
  }
}
