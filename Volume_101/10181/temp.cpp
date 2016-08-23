#include <array>
#include <map>
#include <iostream>
#include <unordered_map>
#include <utility>
namespace std
{
  template<typename T, size_t N>
    struct hash<array<T, N> >
    {
      typedef array<T, N> argument_type;
      typedef size_t result_type;

      result_type operator()(const argument_type& a) const
      {
        hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < N; ++i)
        {
          h = h * 31 + hasher(a[i]);
        }
        return h;
      }
    };
}

using namespace std;

int main() {
  array<int, 3> arr = {2, 3, 4};
  pair<int, array<int, 3>> mypair = {3, arr};
  cout << mypair.first << endl;
  cout << arr[2] << endl;
  arr[1] = 9;
  cout << arr[1] << endl;
  typedef array<int, 3> ARR;
  map<int, ARR> mmm;
  mmm[3] = arr;

  unordered_map<ARR, int> um;
  um[arr] = 23;
  
  cout << um[arr] << endl;
}
