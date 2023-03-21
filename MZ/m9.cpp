#include <iostream>
#include <cstring>
template<typename T>
T maxn(T* arr, size_t n) {
  T max = arr[0];
  for (size_t i = 0; i < n; ++i) {
    max = std::max(arr[i], max);
  }
  return max;
}
template <>
const char* maxn(const char **s, size_t n) {
  const char *maxs = s[0];
  for (size_t i = 0; i < n; i++) {
    maxs = strlen(maxs)  >= strlen(s[i])? maxs: s[i];
  }
  return maxs;
}
/*
int main()
{
  using namespace std;
  int arri[6] = {1, 2, 5, 3, 1, -1};
  double arrd[4] = {2.3, -1.3, 8.7, 4.5};
  const char * arrc[5] = {"first", "second", "third", "long string", "znother string"};

  cout << "max of integer = " << maxn(arri, 1) << endl;
  cout << "max of double = " << maxn(arrd, 2) << endl;
  cout << "max string is " << maxn(arrc, 5) << endl;

  return 0;
}
*/