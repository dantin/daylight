#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  int maxArea(vector<int> &height)
  {
    int start = 0;
    int end = height.size()-1;
    int maxV = INT_MIN;
    while (start < end) {
      int contain = min(height[end], height[start]) * (end-start);
      maxV = max(maxV, contain);
      if (height[start] <= height[end]) {
        start++;
      } else {
        end--;
      }
    }
    return maxV;
  }
};

int main()
{
  vector<int> heights;
  int h;

  while (cin >> h) {
    heights.push_back(h);
  }

  Solution s;
  cout << s.maxArea(heights) << endl;
  
  return 0;
}
