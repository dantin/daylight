// version 1.0 2018-05-08
#include <iostream>

using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3)
  {
    bool *matchUp   = new bool[s2.size()+1];
    bool *matchDown = new bool[s2.size()+1];

    if (s3.size() != (s1.size() + s2.size())) return false;

    // initialize
    matchDown[0] = true;
    for (int i = 1; i < s2.size()+1; ++i) {
      if (s2[i-1] == s3[i-1]) {
        matchDown[i] |= matchDown[i-1];
      } else {
        matchDown[i] = false;
      }
    }
    // vertical loop
    for (int i = 1; i < s1.size()+1; ++i) {
      if (s1[i-1] == s3[i-1]) {
        matchUp[0] |= matchDown[0];
      } else {
        matchUp[0] = false;
      }
      for (int j = 1; j < s2.size()+1; ++j) {
        if (s1[i-1] == s3[i+j-1]) {
          matchUp[j] |= matchDown[j];
        }
        if (s2[j-1] == s3[i+j-1]) {
          matchUp[j] |= matchUp[j-1];
        }
      }
      bool *tmp = matchUp;
      matchUp = matchDown;
      matchDown = tmp;
    }
    delete []matchUp;
    delete []matchDown;

    return matchDown[s2.size()];
  }
};

int main()
{
  string s1, s2, s3;

  cin >> s1 >> s2 >> s3;

  Solution s;
  cout << s.isInterleave(s1, s2, s3) << endl;

  return 0;
}
