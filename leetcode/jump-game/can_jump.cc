// version 1.0 2018-05-14

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool canJump(vector<int> &nums)
  {
    vector<int> jump;
    jump.push_back(0);
    for (int i = 1; i < nums.size(); ++i) {
      jump.push_back(max(jump[i-1], nums[i-1])-1);
      if (jump[i] < 0) {
        return false;
      }
    }
    return jump[nums.size()-1] >= 0;
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
