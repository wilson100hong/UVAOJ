#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

using namespace std;

// First: room light state.
// Second: current room.
typedef pair<int, int> State;

struct Action {
  int moving;
  int switching;
  bool switch_on;
};

struct pair_hash {
  template <class T1, class T2>
  size_t operator() (const pair<T1, T2>& pair) const {
    return hash<T1>()(pair.first << 3) ^ hash<T2>()(pair.second);
  }
};

typedef unordered_map<State, pair<State, Action>, pair_hash> HistoryMap;

void PrintAction(const Action& action) {
  if (action.moving != -1) {
    cout << "- Move to room " << action.moving + 1 << "." << endl;
  } else if (action.switching != -1) {

    cout << "- Switch " << (action.switch_on ? "on" : "off");
    cout << " light in room " << action.switching + 1 << "." << endl;
  }
}

void PrintActions(const vector<Action>& actions) {
  // Print in reverse.
  for (auto rit = actions.rbegin(); rit != actions.rend(); ++rit) {
    PrintAction(*rit);
  }
}

State Advance(
    const vector<set<int>>& doors, const vector<set<int>>& switches,
    const State& curr_state, const Action& action) {
  State next_state = curr_state;
  if (action.moving != -1) {
    next_state.second = action.moving;
  } else if (action.switching != -1) {
    next_state.first = curr_state.first ^ (1 << action.switching);
  }
  return next_state;
}

vector<Action> GetPossibleActions(
    const vector<set<int>>& doors, const vector<set<int>>& switches,
    const State& curr_state) {
  vector<Action> actions;
  const int curr_room = curr_state.second;
  for (int next_room : doors[curr_room]) {
    if (curr_state.first & (1 << next_room)) {  // Next room must be bright.
      actions.push_back({next_room, -1, true});
    }
  }

  for (int light : switches[curr_room]) {
    if (light == curr_room) continue;  // You cannot switch current room.
    bool on = !(curr_state.first & (1 << light));
    actions.push_back({-1, light, on});
  }
  return actions;
}

void Solve(const vector<set<int>>& doors, const vector<set<int>>& switches) {
  int R = doors.size();
  
  State init_state = {1, 0};
  State final_state = {1<<(R-1), R-1};

  //cout << "possible actions" << endl;
  //PrintActions(GetPossibleActions(doors, switches, init_state));
  //cout << "----" << endl;
  

  queue<State> Q;
  Q.push(init_state);

  HistoryMap history_map;
  history_map[init_state] = {init_state, {-1, -1}};

  bool ok = (init_state == final_state);
  while (!ok && !Q.empty()) {
    State state = Q.front();
    Q.pop();
    auto poss_actions = GetPossibleActions(doors, switches, state);
    for (const auto& action : poss_actions) {
      State next_state = Advance(doors, switches, state, action);

      if (history_map.count(next_state)) continue;

      history_map[next_state] = {state, action};
      if (next_state == final_state) {
        ok = true;
        break;
      }
      Q.push(next_state);
    }
  }

  if (ok) {
    State state = final_state;
    vector<Action> actions;
    while (state != init_state) {
      State prev_state;
      Action action;
      tie(prev_state, action) = history_map[state];
      actions.push_back(action);
      state = prev_state;
    }
    cout << "The problem can be solved in " <<  actions.size() << " steps:" << endl;
    PrintActions(actions);
  } else {
    cout << "The problem cannot be solved." << endl;
  }
}

int main() {
  int R, D, S;
  int tc = 1;
  while (cin >> R >> D >> S) {
    if (R == 0 && D == 0 && S == 0) break;
    vector<set<int>> doors(R, set<int>());
    vector<set<int>> switches(R, set<int>());
    for (int i=0;i<D;++i) {
      int u, v;
      cin >> u >> v;
      u--; v--;  // 0-based.
      doors[u].insert(v);
      doors[v].insert(u);
    }
    for (int i=0;i<S;++i) {
      int k, l;
      cin >> k >> l;
      k--; l--;  // 0-based.
      switches[k].insert(l);
    }

    cout << "Villa #" << tc++ << endl;
    Solve(doors, switches);
    cout << endl;
  }
}
