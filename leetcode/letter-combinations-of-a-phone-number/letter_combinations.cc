// version 1.0 2018-05-28
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
      string trans[] = { "", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
      vector<string> set;
      string seq;

      // ignore empty input in a quick and dirty way.
      if (digits.size() == 0) return set;

      generate(trans, digits, 0, seq, set);

      return set;
    }

private:
    void generate(string trans[], string &digits, int deep, string &result, vector<string> &set)
    {
      if (deep == digits.size()) {
        set.push_back(result);
        return;
      }

      // convert ASCII code to integer
      int curDig = digits[deep] - 48;
      for (int i = 0; i < trans[curDig].size(); ++i) {
        result.push_back(trans[curDig][i]);
        generate(trans, digits, deep+1, result, set);
        result.resize(result.size()-1);
      }
    }
};

int main()
{
  string digits;

  cin >> digits;

  Solution s;
  auto combs = s.letterCombinations(digits);

  for (auto comb : combs) {
    cout << comb << endl;
  }
  cout << endl;

  return 0;
}
