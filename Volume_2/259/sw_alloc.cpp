#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct App {
    char symbol;
    vector<int> computers;
};

struct Computer {
    int index;
    vector<int> apps;
};

void Reset(vector<Computer>& computers) {
    for (int i = 0; i < computers.size(); ++i) {
        computers[i].apps.clear();
    }
}

void Dump(vector<Computer>& computers,
        vector<App>& apps) {

    cout << "Computers:" << endl;
    for (int i = 0; i < computers.size(); ++i) {
        cout << i << " : ";
        for (int j = 0; j < computers[i].apps.size(); ++j) {
            cout << computers[i].apps[j] << ",";
        }
        cout << endl;
    }
    cout << "Apps:" << endl;
    for (int i = 0; i < apps.size(); ++i) {
        cout << i << " : ";
        for (int j = 0; j < apps[i].computers.size(); ++j) {
            cout << apps[i].computers[j] << ",";
        }
        cout << endl;
    }
}

bool DFS(int cpu_index,
        vector<Computer>& computers,
        vector<App>& apps,
        vector<int>& m_c,
        vector<int>& m_a,
        vector<bool>& v_a) {

    for (int i = 0; i < computers[cpu_index].apps.size(); ++i) {
        int app_index = computers[cpu_index].apps[i];
        if (!v_a[app_index]) {
            v_a[app_index] = true;
            if (m_a[app_index] == -1 ||
                    DFS(m_a[app_index], computers, apps, m_c, m_a, v_a)) {
                m_c[cpu_index] = app_index;
                m_a[app_index] = cpu_index;
                return true;
            }
        }
    }
    return false;
}

void BiMatch(vector<Computer>& computers, vector<App>& apps) {
    vector<int> m_c;  // matched computers
    vector<int> m_a;  // matched apps
    vector<bool> v_a;  // visit apps
    for (int i = 0; i < computers.size(); ++i) {
        m_c.push_back(-1);
    }
    for (int i = 0; i < apps.size(); ++i) {
        m_a.push_back(-1);
        v_a.push_back(false);
    }

    int cnt = 0;
    for (int i = 0; i < computers.size(); ++i) {
        if (m_c[i] == -1) {
            if (DFS(i, computers, apps, m_c, m_a, v_a))
                cnt++;
        }
        // clare visit
        for (int j = 0; j < v_a.size(); ++j) {
            v_a[j] = false;
        }
    }

    if (cnt < apps.size()) {
        cout << "!";
    } else {
        for (int i = 0; i < m_c.size(); ++i) {
            if (m_c[i] == -1)  cout << "_";
            else cout << apps[m_c[i]].symbol;
        }
    }
    cout << endl;
}

int main() {
    string line;
    vector<Computer> computers;
    vector<App> apps;

    // Initialization
    for (int i = 0; i < 10; ++i) {
        Computer cpu;
        cpu.index = i;
        computers.push_back(cpu);
    }

    int cc = 0;
    while (getline(cin, line)) {
        if (line == "" || line == " ") {
            BiMatch(computers, apps);
            //Dump(computers, apps);
            Reset(computers);
            apps.clear();
        } else {
            stringstream ss(line);
            char symbol;
            int cnt;
            string cand_list;
            ss >> symbol >> cnt >> cand_list;

            vector<int> candidates;
            for (int i = 0; i < cand_list.length(); ++i) {
                char c = cand_list[i];
                if ('0' <= c && c <= '9') {
                    candidates.push_back((int) c - '0');
                }
            }

            for (int i = 0; i < cnt; ++i) {
                App app;
                app.symbol = symbol;
                // create app -> computer edges
                app.computers = candidates;  // Assign copy
                int app_index = apps.size();
                apps.push_back(app);

                // create computer -> app edges
                for (int j = 0; j < candidates.size(); ++j) {
                    int cpu_index = candidates[j];
                    computers[cpu_index].apps.push_back(app_index);
                }
            }
        }
    }

    BiMatch(computers, apps);
}

