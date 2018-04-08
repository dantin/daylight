#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    map<int, int> mapping;
    vector<int> result;
    for (int i = 0; i < numbers.size(); i++) {
      mapping[numbers[i]] = i;
    }

    for (int i = 0; i < numbers.size(); i++) {
      int searched = target - numbers[i];
      if (mapping.find(searched) != mapping.end() &&
          i != mapping[searched]) {
        result.push_back(i+1);
        result.push_back(mapping[searched]+1);
        break;
      }
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
