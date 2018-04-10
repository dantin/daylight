#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &num, int target)
  {
    vector<vector<int>> result;
    vector<int> solution;
    int sum = 0;
    sort(num.begin(), num.end());
    getCombination(num, sum, 0, target, solution, result);
    return result;
  }

  void getCombination(vector<int> &candidates,
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
    for (int i = level; i < candidates.size(); ++i) {
      sum += candidates[i];
      solution.push_back(candidates[i]);
      getCombination(candidates, sum, i+1, target, solution, result);
      solution.pop_back();
      sum -= candidates[i];
      while (i < candidates.size() - 1 &&
             candidates[i] == candidates[i+1]) {
        i++;
      }
    }
  }
};

int main()
{
  vector<int> nums;
  int target, n;

  cin >> target;
  while (cin >> n) nums.push_back(n);

  Solution s;
  vector<vector<int>> ans = s.combinationSum(nums, target);

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
