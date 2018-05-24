#include <iostream>

using namespace std;

class Solution {
  public:
    int lengthOfLastWorld(string s)
    {
      int len = s.size();
      int count = 0;
      for (int i = len-1; i >= 0; --i) {
        if (s[i] == ' ') {
          if (count == 0) continue;
          else return count;
        }
        count++;
      }
      return count;
    }
};

int main()
{
  string str;

  cin >> str;

  Solution s;
  cout << s.lengthOfLastWorld(str) << endl;

  return 0;
}
