#include <iostream>

using namespace std;

class Solution {
public:
  int reverse(int x) {
    int ans = 0;
    while (x) {
      int t = ans * 10 + x % 10;
      // check to make sure overflow conditions.
      if (t/10 != ans) {
        return 0;
      }
      ans = t;
      x /= 10;
    }
    return ans;
  }
};

int main() {
  int num;
  cin >> num;
  Solution s;
  cout << s.reverse(num) << endl;
  return 0;
}
