#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums)
  {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int len = nums.size();
    for (int i = 0; i < len; i++) {
        int target = 0 - nums[i];
        int start = i + 1, end = len - 1;
        while (start < end) {
          if (nums[start] + nums[end] == target) {
            vector<int> solution;
            solution.push_back(nums[i]);
            solution.push_back(nums[start]);
            solution.push_back(nums[end]);
            result.push_back(solution);
            start++; end--;
            while (start < end &&
                   nums[start] == nums[start - 1]) {
              start++;
            }
            while (start < end &&
                   nums[end] == nums[end+1]) {
              end--;
            }
          } else if (nums[start] + nums[end] < target) {
            start++;
          } else {
            end--;
          }
        }
        if (i < len-1) {
          while (nums[i] == nums[i+1]) { i++; }
        }
    }
    return result;
  }
};

int main()
{
  vector<int> nums;
  int input;

  while (cin >> input) {
    nums.push_back(input);
  }

  Solution s;
  vector<vector<int>> results = s.threeSum(nums);
  for (int i = 0; i < results.size(); i++) {
    for (int j = 0; j < results[i].size(); j++) {
      cout << results[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}
