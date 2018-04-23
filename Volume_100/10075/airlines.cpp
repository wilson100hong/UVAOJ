/*
 *  04/22/2018
 *
 *  TRAP: for each pair of cities, round to nearest integer
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <limits>
using namespace std;
 
#define EARTH_R 6378
#define PI 3.141592653589793
 
#define MAX 1000000 // should be enough

struct Location {
    // in radiance
    double lat;
    double lng;
};

double rad(double degree) {
    return degree * PI / 180.0;
}

double haversine(double a) {
    return (1 - cos(a)) / 2.0;
}

double distance(const Location& l1, const Location& l2) {
    double halpha = haversine(l1.lat - l2.lat) + cos(l1.lat)*cos(l2.lat)*haversine(l1.lng - l2.lng);
    return 2* EARTH_R * asin(sqrt(halpha));
}

int main() {
    map<string, int> ci;  // city index
    vector<Location> locs;
    vector<vector<unsigned long>> dist;

    int T = 0;
    int N, M, Q;
    while (cin >> N >> M >> Q) {
        // reset
        ci.clear();
        dist.clear();
        locs.clear();
        if (N == 0 && M == 0 && Q == 0) break;

        while (N--) {
            string city;
            double lat, lng;
            cin >> city >> lat >> lng;
            ci[city] = ci.size();
            locs.push_back({rad(lat), rad(lng)});
        }
        N = ci.size();
        dist.assign(N, vector<unsigned long>(N, MAX));
    
        while (M--) {
            string s1, s2;
            cin >> s1 >> s2;
            int c1 = ci[s1], c2 = ci[s2];
            double d = distance(locs[c1], locs[c2]);
            //dist[c1][c2] = dist[c2][c1] = d;
            // round for each pair of cities
            dist[c1][c2] = static_cast<int>(d+0.5);
        }

        // floyd-warshall
        for (int k=0;k<N;++k) {
            for (int i=0;i<N;++i) {
                for (int j=0;j<N;++j) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) { 
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        if (T) cout << endl;
        cout << "Case #" << ++T << endl;

        while (Q--) {
            string s1, s2;
            cin >> s1 >> s2;
            int c1 = ci[s1], c2 = ci[s2];
            int d = dist[c1][c2];
            if (d == MAX) {
                cout << "no route exists" << endl;
            } else {
                cout << d << " km" << endl;
            }
        }
    }

    //Location l1 = {rad(23.85), rad(90.4)};
    //Location l2 = {rad(22.25), rad(91.8333)};
}
