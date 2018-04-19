#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n)
  {
    vector<string> result;
    string sample;
    if (n != 0) {
      combinationPar(result, sample, 0, n, 0, 0);
    }
    return result;
  }
  
private:
  void combinationPar(vector<string> &result,
                      string &sample,
                      int deep,
                      int n,
                      int leftNum,
                      int rightNum)
  {
    if (deep == 2*n) {
      result.push_back(sample);
      return;
    }
    if (leftNum < n) {
      sample.push_back('(');
      combinationPar(result, sample, deep+1, n, leftNum+1, rightNum);
      sample.resize(sample.size()-1);
    }
    if (rightNum < leftNum) {
      sample.push_back(')');
      combinationPar(result, sample, deep+1, n, leftNum, rightNum+1);
      sample.resize(sample.size()-1);
    }
  }
};

int main()
{
  int n;

  cin >> n;

  Solution s;
  vector<string> solutions = s.generateParenthesis(n);

  for (auto e : solutions) {
    cout << e << endl;
  }

  return 0;
}
