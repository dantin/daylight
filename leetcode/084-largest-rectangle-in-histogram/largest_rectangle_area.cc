// version 1.0 2018-05-23
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
  public:
    int largestRectangleArea(vector<int> &heights)
    {
      stack<int> s;
      heights.push_back(0);  // last trigger
      int sum = 0;
      for (int i = 0; i < heights.size(); ++i) {
        if (s.empty() || heights[i] > heights[s.top()]) {
          s.push(i);
        } else {
          int tmp = s.top();
          s.pop();
          sum = max(sum, heights[tmp]*(s.empty() ? i : i-s.top()-1));
          i--;
        }
      }

      return sum;
    }
};

int main()
{
  int n, h;
  vector<int> heights;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> h;
    heights.push_back(h);
  }

  Solution s;
  cout << s.largestRectangleArea(heights) << endl;

  return 0;
}
