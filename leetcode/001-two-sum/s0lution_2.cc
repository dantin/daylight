#include <vector>
#include <iostream>

using namespace std;

struct Node
{
  int val;
  int index;
  Node(int pVal, int pIndex):val(pVal), index(pIndex) {}
};

static bool compare(const Node &left, const Node &right)
{
  return left.val < right.val;
}

class Solution {
public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<Node> elements;

    for (int i = 0; i < numbers.size(); i++) {
      elements.push_back(Node(numbers[i], i));
    }

    sort(elements.begin(), elements.end(), compare);

    int start = 0, end = numbers.size() - 1;
    vector<int> result;

    while (start < end) {
      int sum = elements[start].val + elements[end].val;
      if (sum == target) {
        result.push_back(elements[start].index + 1);
        if (elements[start].index < elements[end].index)
          result.push_back(elements[end].index + 1);
        else
          result.insert(result.begin(), elements[end].index+1);
        break;
      } else if (sum > target)
        end--;
      else
        start++;
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
