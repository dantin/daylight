// Solution of strStr
//
// version 1.0 2018-04-28
#include <iostream>

using namespace std;

class Solution {
public:
  int strStr(string haystack, string needle)
  {
    if (needle.empty()) return 0;
    int hLen = haystack.size();
    int nLen = needle.size();
    if (hLen < nLen) return -1;
    for (int i = 0; i < hLen-nLen+1; ++i) {
      int j = 0;
      for (j = 0; j < nLen; ++j) {
        if (haystack[i+j] != needle[j]) break;
      }
      if (j == nLen) return i;

    }
    return -1;
  }
};

int main()
{
  int n;
  Solution s;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    string haystack, needle;

    cin >> haystack;
    cin >> needle;

    cout << "haystack = " << haystack
         << ", needle = " << needle
         << ", output = " << s.strStr(haystack, needle)
         << endl;
  }
  return 0;
}
