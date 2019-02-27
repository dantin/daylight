#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> grayCode(int n)
  {
    vector<int> res;
    int size = 1 << n;
    for (int i = 0; i < size; ++i) {
      res.push_back((i >> 1)^i);
    }
    return res;
  }
};

int main()
{
  int n;

  cin >> n;

  Solution s;
  vector<int> res = s.grayCode(n);

  bool head = true;
  for (auto n : res) {
    if (!head) cout << ", ";
    cout << n;
    head = false;
  }
  cout << endl;

  return 0;
}
