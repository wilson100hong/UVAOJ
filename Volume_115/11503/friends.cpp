#include <iostream>
#include <unordered_map>
using namespace std;

string group(unordered_map<string, string>& parent,
             const string& name) {
  if (name != parent[name]) {
    parent[name] = group(parent, parent[name]);
  }
  return parent[name];
}

int join(unordered_map<string, string>& parent,
         unordered_map<string, int>& number,
         const string& name1,
         const string& name2) {
  if (group(parent, name1) != group(parent, name2)) {
    number[group(parent, name2)] += number[group(parent, name1)];
    parent[group(parent, name1)] = group(parent, name2);
  }
  return number[group(parent, name1)];
}

void maybe_add_name(
    unordered_map<string, string>& parent,
    unordered_map<string, int>& number,
    const string& name) {
  if (!parent.count(name)) {
    parent[name] = name;
    number[name] = 1;
  }
}

int main() {
  int cases;
  unordered_map<string, string> parent;
  unordered_map<string, int> number;
  cin >> cases;
  while (cases--) {
    parent.clear();
    number.clear();
    int F;
    cin >> F;
    while (F--) {
      string name1, name2;
      cin >> name1 >> name2;
      maybe_add_name(parent, number, name1);
      maybe_add_name(parent, number, name2);
      cout << join(parent, number, name1, name2) << endl;
    }
  }
}
