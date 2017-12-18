#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> h;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
      int remains = target - nums[i];
      if (h.find(remains) != h.end()) {
        result.push_back(h[remains]);
        result.push_back(i);
        return result;
      }
      h[nums[i]] = i;
    }
    return result;
  }
};

int main() {
  vector<int> nums;
  int input, target;

  cin >> target;
  while (cin >> input) {
    nums.push_back(input);
  }

  Solution s;
  vector<int> idx = s.twoSum(nums, target);
  cout << idx[0] << ", " << idx[1] << endl;
  
  return 0;
}
