#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices)
  {
    int minV = INT_MAX;
    int max = 0;
    int diff = 0;
    for (int i = 0; i < prices.size(); ++i) {
      if (prices[i] < minV) minV = prices[i];
      diff = prices[i] - minV;
      if (max < diff) {
        max = diff;
      }
    }
    return max;
  }
};

int main()
{
  vector<int> prices;
  int price;

  while (cin >> price) prices.push_back(price);

  Solution s;
  cout << s.maxProfit(prices) << endl;

  return 0;
}
