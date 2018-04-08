#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<vector<string>> result;
    if (strs.size() == 0) return result;
    map<long, vector<string>> smap;
    for (int i = 0; i < strs.size(); i++) {
      smap[footprint(strs[i])].push_back(strs[i]);
    }
    for (auto it = smap.begin(); it != smap.end(); ++it) {
      result.push_back(it->second);
    }
    return result;
  }

  long footprint(string str)
  {
    int index[26];
    memset(index, 0, 26*sizeof(int));
    for (int i = 0; i < str.size(); ++i) {
      index[str[i]-'a']++;
    }
    /*string footp;
    for (int i = 0; i < 26; i++)
      {
        footp.append(1, i+'a');
        stringstream ss;
        ss << index[i];
        footp.append(ss.str());
      }*/
    long footp = 0;
    int feed = 7;
    for (int i = 0; i < 26; ++i) {
      footp = footp * feed + index[i];
    }
    return footp;
  }
};

int main()
{
  vector<string> strs;
  string str;

  while (cin >> str) {
    strs.push_back(str);
  }

  Solution s;
  vector<vector<string>> amap = s.groupAnagrams(strs);
  for (int i = 0; i < amap.size(); ++i) {
    bool is_sep = false;
    cout << "[ ";
    for (int j = 0; j < amap[i].size(); ++j) {
      if (is_sep) cout << ", ";
      cout << amap[i][j];
      is_sep = true;
    }
    cout << " ]";
    cout << endl;
  }
  return 0;
}
