// Need to use Haversine formula: http://mathforum.org/library/drmath/view/51879.html
// But doesn't have good test case to prove that
#include <iostream>
#include <map>
#include <sstream>
#include <math.h>

using namespace std;
#define PI 3.141592653589793
#define R 6378.0

struct Point {
  // in radius
  double lat;
  double lon;  
};

//double distance(const Point& p1, const Point& p2) {
  //double dlon = p1.lon - p2.lon;
  //return R * acos(cos(p1.lat) * cos(p2.lat) * cos(dlon) + sin(p1.lat) * sin(p2.lat));
//}

// Haversine
double distance2(const Point& p1, const Point& p2) {
  double dlon = p2.lon - p1.lon;
  double dlat = p2.lat - p1.lat;
  double a = (sin(dlat/2))*(sin(dlat/2)) + cos(p1.lat) * cos(p2.lat) * (sin(dlon/2))*(sin(dlon/2));
  double c = 2*atan2(sqrt(a), sqrt(1-a)) ;
  return R * c;
}

int main() {
  // read cities
  map<string, Point> cities;
  string line;
  while (getline(cin, line)) {
    if (line == "#") break;
    stringstream ss(line);
    string name;
    double lat_deg, lon_deg;
    ss >> name >> lat_deg >> lon_deg;
    Point city = {lat_deg * PI / 180.0, lon_deg * PI / 180.0};
    cities[name] = city;
  }
  // queries
  while (getline(cin, line)) {
    if (line == "# #") break;
    stringstream ss(line);
    string n1, n2;
    ss >> n1 >> n2;
    cout << n1 << " - " << n2 << endl;
    if (cities.count(n1) == 0 || cities.count(n2) == 0) {
      cout << "Unknown" << endl;
    } else {
      //double dist = distance(cities[n1], cities[n2]) + 0.5;
      //int ans = dist;
      //cout << ans << " km" << endl;
      double dist2 = distance2(cities[n1], cities[n2]) + 0.5;
      int ans2 = dist2;
      cout << ans2 << " km" << endl;
    }
  }
}
