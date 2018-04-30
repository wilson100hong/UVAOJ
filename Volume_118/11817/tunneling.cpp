#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159265358979323846
#define R 6371009

typedef unsigned long long ULL;

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

double great_circle_dist(const Location& l1, const Location& l2) {
    double halpha = haversine(l1.lat - l2.lat) + cos(l1.lat)*cos(l2.lat)*haversine(l1.lng - l2.lng);
    return 2* R * asin(sqrt(halpha));
}

double tunnel_dist(const Location& l1, const Location& l2) {
    double x1 = cos(l1.lat)*cos(l1.lng);
    double y1 = cos(l1.lat)*sin(l1.lng);
    double z1 = sin(l1.lat);

    double x2 = cos(l2.lat)*cos(l2.lng);
    double y2 = cos(l2.lat)*sin(l2.lng);
    double z2 = sin(l2.lat);

    double dx = x1-x2, dy = y1-y2, dz=z1-z2;
    double d2 = dx*dx + dy*dy + dz*dz;
    return R*sqrt(d2);
}

ULL solve(const Location& l1, const Location& l2) {
    return static_cast<ULL>(great_circle_dist(l1, l2) - tunnel_dist(l1, l2) + 0.5);
}

int main() {
    int T;
    Location l1, l2;
    double lat1, lng1, lat2, lng2;
    cin >> T;
    while (T--) {
        cin >> lat1 >> lng1 >> lat2 >> lng2;
        l1 = {rad(lat1), rad(lng1)};
        l2 = {rad(lat2), rad(lng2)};
        cout << solve(l1, l2) << endl;
    }
}
