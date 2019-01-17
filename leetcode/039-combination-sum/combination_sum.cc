#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target)
  {
    vector<vector<int>> result;
    vector<int> solution;
    int sum = 0;
    sort(candidates.begin(), candidates.end());
    getCombinations(candidates, sum, 0, target, solution, result);
    return result;
  }

  void getCombinations(vector<int> &candidates,
                       int &sum,
                       int level,
                       int target,
                       vector<int> &solution,
                       vector<vector<int>> &result)
  {
    if (sum > target) return;
    if (sum == target) {
      result.push_back(solution);
      return;
    }
    for (int i = level; i < candidates.size(); i++) {
      sum += candidates[i];
      solution.push_back(candidates[i]);
      getCombinations(candidates, sum, i, target, solution, result);
      solution.pop_back();
      sum -= candidates[i];
    }
  }
};

int main()
{
  vector<int> numbers;
  int i, target;

  cin >> target;
  while (cin >> i) numbers.push_back(i);

  Solution s;
  vector<vector<int>> ans = s.combinationSum(numbers, target);

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
