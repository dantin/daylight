// version 1.0 2018-05-05
#include <iostream>

using namespace std;

class Solution {
public:
  string intToRoman(int num)
  {
    // symbol of 1, 5, 10, 50, 100, 500, 1000
    char symbol[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    string roman;
    int scale = 1000;
    for (int i = 6; i >= 0; i -= 2) {
      int digit = num / scale;
      if (digit != 0) {
        if (digit <= 3) {
          roman.append(digit, symbol[i]);
        } else if (digit == 4) {
          roman.append(1, symbol[i]);
          roman.append(1, symbol[i+1]);
        } else if (digit == 5) {
          roman.append(1, symbol[i+1]);
        } else if (digit <= 8) {
          roman.append(1, symbol[i+1]);
          roman.append(digit-5, symbol[i]);
        } else if (digit == 9) {
          roman.append(1, symbol[i]);
          roman.append(1, symbol[i+2]);
        }
      }
      num %= scale;
      scale /= 10;
    }
    return roman;
  }
};

int main() {
  int n;
  cin >> n;

  Solution s;
  cout << s.intToRoman(n) << endl;

  return 0;
}
