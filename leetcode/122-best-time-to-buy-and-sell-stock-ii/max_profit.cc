#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices)
  {
    int max = 0;
    int sum = 0;
    for (int i = 1; i < prices.size(); ++i) {
      int diff = prices[i] - prices[i-1];
      if (diff > 0) {
        sum += diff;
      }
    }
    return sum;
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
