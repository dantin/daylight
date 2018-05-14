#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool canJump(vector<int> &nums)
  {
    int maxCover = 0;

    for (int i = 0; i <= maxCover && i < nums.size(); ++i) {
      if (nums[i] + i > maxCover) {
        maxCover = nums[i] + i;
      }
      if (maxCover >= nums.size()-1) return true;
    }

    return false;
  }
};

int main()
{
  int n, num;
  vector<int> nums;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> num;
    nums.push_back(num);
  }

  Solution s;
  cout << s.canJump(nums) << endl;

  return 0;
}
