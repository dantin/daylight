// version 1.0 2018-05-15

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int jump(vector<int> &nums)
  {
    int start = 0;
    int end = 0;
    int count = 0;
    if (nums.size() == 1) {
      return 0;
    }
    while (end < nums.size()) {
      int max = 0;
      count++;
      for (int i = start; i <= end; i++) {
        if (nums[i]+i >= nums.size()-1) {
          return count;
        }
        if (nums[i]+i > max) {
          max = nums[i]+i;
        }
      }
      start = end+1;
      end = max;
    }

    return 0;
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
  cout << s.jump(nums) << endl;

  return 0;
}
