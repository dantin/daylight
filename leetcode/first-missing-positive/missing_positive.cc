#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int firstMissingPositive(vector<int> &nums)
  {
    int i = 0;
    int n = nums.size();
    for (i = 0; i < n; ++i) {
      while (nums[i] != i+1) {
        if (nums[i] <= 0 ||
            nums[i] > n ||
            nums[i] == nums[nums[i]-1]) {
          break;
        }
        int tmp = nums[i];
        nums[i] = nums[tmp-1];
        nums[tmp-1] = tmp;
      }
    }
    for (i = 0; i < n; ++i) {
      if (nums[i] != i+1) {
        return i+1;
      }
    }
    return n+1;
  }
};

int main()
{
  vector<int> nums;
  int n;

  while (cin >> n) nums.push_back(n);

  Solution s;
  cout << s.firstMissingPositive(nums) << endl;

  return 0;
}
