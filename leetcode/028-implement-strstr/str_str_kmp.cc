// Solution of strStr()
//
// version 1.0 2018-04-28
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int strStr(string haystack, string needle)
  {
    int hLen = haystack.size();
    int nLen = needle.size();
    if (hLen < nLen) return -1;
    if (!nLen) return 0;

    vector<int> kmp(nLen, 0);
    buildKMP(needle, kmp);

    return match(haystack, needle, kmp);
  }
private:
  void buildKMP(const string &str, vector<int> &pattern)
  {
    int sLen = str.size();
    int i = 2, j = 0;

    pattern[0] = -1;
    if (sLen > 1) pattern[1] = 0;
    while (i < sLen) {
      if (str[i-1] == str[j]) pattern[i++] = ++j;
      else if (j > 0) j = pattern[j];
      else pattern[i++] = 0;
    }
  }

  int match(string haystack, string needle, vector<int> &pattern)
  {
    int start = 0, i = 0;
    int hLen = haystack.size(), nLen = needle.size();
    while (start <= hLen-nLen) {
      if (haystack[start+i] == needle[i]) {
        if (++i == nLen) return start;
      } else {
        start = start+i-pattern[i];
        i = i>0 ? pattern[i] : 0;
      }
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
