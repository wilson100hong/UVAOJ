#include <iostream> 
using namespace std;

enum Dir {
    Px = 0,
    Nx,
    Py,
    Ny,
    Pz,
    Nz
};

Dir bend_y[] = {Px, Py, Nx, Ny};
Dir bend_z[] = {Px, Pz, Nx, Nz};

int find_bend_index(Dir* array, Dir d) {
    for (int i=0;i<4;++i) {
        if (array[i] == d) return i;
    }
    return -1;
}

void print(Dir d) {
    switch (d) {
        case Px:
            cout << "+x";
            break;
        case Nx:
            cout << "-x";
            break;
        case Py: 
            cout << "+y";
            break;
        case Ny:
            cout << "-y";
            break;
        case Pz:
            cout << "+z";
            break;
        case Nz:
            cout << "-z";
            break;
    }
    cout << endl;
}

int main() {
    int L;
    while (cin >> L) {
        if (L == 0) break;
        Dir d = Px;
        while (--L) {
            string action;
            cin >> action;
            if (action == "No") continue;
            int delta = (action[0] == '+' ? 1 : -1);
            Dir* array = (action[1] == 'y' ? bend_y : bend_z);
            int index = find_bend_index(array, d);
            if (index == -1) continue;
            index = (index + 4 + delta) % 4;
            d = array[index];
        }
        print(d);
    }
}
