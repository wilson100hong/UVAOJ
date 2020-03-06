#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

bool IsMisspelled(const string& s1, const string& s2) {
  int n1 = s1.size(), n2 = s2.size();
  int dlen = abs(n1 - n2);
  if (dlen >= 2) return false;
  
  int i=0, j=0;
  while (i < n1 && j < n2) {
    if (s1[i] != s2[j]) break;
    i++; j++;
  }

  // handle s1[i] and s2[j]
  if (n1 < n2) {
    j++;
  } else if (n1 > n2) {
    i++;
  } else {
    // switch letter
    if (i < n1-1 && (s1[i+1] == s2[j] && s2[j+1] == s1[i])) {
      i+=2; j+=2;
    } else {
      // wrong letter
      i++; j++;
    }
  }

  while (i < n1 && j < n2) {
    if (s1[i] != s2[j]) {
      return false;
    }
    i++; j++;
  }

  if (i != n1 || j != n2){
    return false;
  }

  return true;
}

int main() {
  vector<string> dictionary;
  string line;
  int N, Q;
  cin >> N; getline(cin, line);
  while (N--) {
    getline(cin, line);
    dictionary.push_back(line);
  }

  set<string> dict_set(dictionary.begin(), dictionary.end());

  cin >> Q; getline(cin, line);
  while (Q--) {
    getline(cin, line);
    cout << line << " ";
    if (dict_set.count(line)) {
      cout << "is correct" << endl;
    } else {
      bool ok = false;
      for (const string& word : dictionary) {
        if (IsMisspelled(word, line)) {
          cout << "is a misspelling of " << word << endl;
          ok = true;
          break;
        }
      }
      if (!ok) {
        cout << "is unknown" << endl;
      }
    }
  }
}
