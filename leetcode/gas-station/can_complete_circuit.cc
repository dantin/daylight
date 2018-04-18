#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
  {
    vector<int> diff(gas.size());
    for (int i = 0; i < gas.size(); ++i) {
      diff[i] = gas[i] - cost[i];
    }
    int leftGas = 0, sum = 0, startNode = 0;
    for (int i = 0; i < gas.size(); ++i) {
      leftGas += diff[i];
      sum += diff[i];
      if (sum < 0) {
        startNode = i + 1;
        sum = 0;
      }
    }
    if (leftGas < 0) {
      return -1;
    } else {
      return startNode;
    }
  }
};

int main()
{
  vector<int> gas, cost;
  int e, n;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> e;
    gas.push_back(e);
  }
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> e;
    cost.push_back(e);
  }

  Solution s;
  cout << s.canCompleteCircuit(gas, cost) << endl;

  return 0;
}
