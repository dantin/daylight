#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combine(int n, int k)
  {
    vector<vector<int>> result;
    vector<int> solution;
    getCombine(n, k, 1, solution, result);
    return result;
  }

  void getCombine(int n,
                  int k,
                  int level,
                  vector<int> &solution,
                  vector<vector<int>> &result)
  {
    if (solution.size() == k) {
      result.push_back(solution);
      return;
    }
    for (int i = level; i <= n; ++i) {
      solution.push_back(i);
      getCombine(n, k, i+1, solution, result);
      solution.pop_back();
    }
  }
};

int main()
{
  int n, k;

  cin >> n >> k;

  Solution s;
  vector<vector<int>> ans = s.combine(n, k);

  for (auto item : ans) {
    cout << "[";
    bool head = true;
    for (auto i : item) {
      if (!head) cout << ", ";
      cout << i;
      head = false;
    }
    cout << "]" << endl;
  }

  return 0;
}
